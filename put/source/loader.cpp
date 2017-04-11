#include "loader.h"
#include "memory.h"
#include "file_system.h"
#include "renderer.h"
#include "pen_string.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

namespace put
{
#define DDS_RGBA 0x01
#define DDS_BC	 0x04

#define DXT1	 0x31545844	 
#define DXT2	 0x32545844	 
#define DXT3	 0x33545844	 
#define DXT4	 0x34545844	 
#define DXT5	 0x35545844	 
#define DX10	 0x30315844	 

    //dds documentation os MSDN defines all these data types as ulongs
    typedef struct dds_pixel_format
    {
        u32 size;
        u32 flags;
        u32 four_cc;
        u32 rgb_bit_count;
        u32 r_mask;
        u32 g_mask;
        u32 b_mask;
        u32 a_mask;
        
    } dds_pixel_format;
    
    typedef struct dds_header
    {
        u32             magic;
        u32				size;
        u32				flags;
        u32				height;
        u32				width;
        u32				pitch_or_linear_size;
        u32				depth;
        u32				mip_map_count;
        u32				reserved[11];
        dds_pixel_format	pixel_format;
        u32				caps;
        u32				caps2;
        u32				caps3;
        u32				caps4;
        u32				reserved2;
    } dds_header;

	u32 calc_level_size( u32 width, u32 height, bool compressed, u32 block_size )
	{
		if( compressed )
		{
			return PEN_UMAX( 1, ( ( width + 3 ) / 4 ) ) * PEN_UMAX( 1, ( ( height + 3 ) / 4 ) ) * block_size;
		}

		return	width * height * block_size; 		
	}

	u32 dds_pixel_format_to_texture_format( const dds_pixel_format &ddspf, bool &compressed, u32 &block_size, bool &dx10_header_present )
	{
		dx10_header_present = false;
		compressed = false;

		if( ddspf.four_cc )
		{
			compressed = true;
			block_size = 16;

			switch( ddspf.four_cc )
			{
			case DXT1:
				block_size = 8;
				return PEN_TEX_FORMAT_BC1_UNORM;
			case DXT2:
				return PEN_TEX_FORMAT_BC2_UNORM;
			case DXT3:
				return PEN_TEX_FORMAT_BC3_UNORM;
			case DXT4:
				return PEN_TEX_FORMAT_BC4_UNORM;
			case DXT5:
				return PEN_TEX_FORMAT_BC5_UNORM;
			case DX10:
				dx10_header_present = true;
				return 0;
			}
		}
		else
		{
			u32 rgba = (ddspf.r_mask | ddspf.g_mask | ddspf.b_mask | ddspf.a_mask);
			if ( rgba == 0xffffffff)
			{
				block_size = 4;
				return PEN_TEX_FORMAT_BGRA8_UNORM;
			}
		}

		//only supported formats are RGBA 
		PEN_ASSERT( 0 );

		return 0;
	}

	pen::texture_creation_params* loader_load_texture( const c8* filename )
	{
		//load a texture file from disk.
		void* file_data = NULL;
		u32	  file_data_size = 0;
        
		u32 pen_err = pen::filesystem_read_file_to_buffer( filename, &file_data, file_data_size );
        
        if( pen_err != PEN_ERR_OK )
        {
            pen::memory_free( file_data );
            return nullptr;
        }
        
        pen::texture_creation_params* tcp = (pen::texture_creation_params*)pen::memory_alloc( sizeof( pen::texture_creation_params ) );

		//parse dds header
		dds_header* ddsh = (dds_header*)file_data;

		bool dx10_header_present;
		bool compressed;
		u32	 block_size;

		u32 format = dds_pixel_format_to_texture_format( ddsh->pixel_format, compressed, block_size, dx10_header_present );

		//fill out texture_creation_params
		tcp->width = ddsh->width;
		tcp->height = ddsh->height;
		tcp->format = format;
		tcp->num_mips = ddsh->mip_map_count;
		tcp->num_arrays = 1;
		tcp->sample_count = 1;
		tcp->sample_quality = 0;
		tcp->usage = PEN_USAGE_DEFAULT;
		tcp->bind_flags = PEN_BIND_SHADER_RESOURCE;
		tcp->cpu_access_flags = 0;
		tcp->flags = 0;
		tcp->block_size = block_size;
		tcp->pixels_per_block =  compressed ? 4 : 1;

		//allocate and copy texture data

		//top level
		u32 data_size = calc_level_size( tcp->width, tcp->height, compressed, block_size );
		
		//mips / faces / slices / depths
		u32 ext_data_size = 0;

		u32 mip_width = tcp->width >> 1;
		u32 mip_height = tcp->height >> 1;

		for( u32 i = 0; i < tcp->num_mips; ++i )
		{
			ext_data_size += calc_level_size( mip_width, mip_height, compressed, block_size );

			mip_width = mip_width > 1 ? mip_width >> 1 : 1;
			mip_height = mip_height > 1 ? mip_height >> 1 : 1;
		}

		tcp->data_size = data_size + ext_data_size;
		tcp->data = pen::memory_alloc( tcp->data_size  );

		//copy texture data s32o the tcp storage
		u8* top_image_start = (u8*)file_data + sizeof( dds_header );
		u8* ext_image_start = top_image_start + data_size;

		pen::memory_cpy( tcp->data, top_image_start, data_size );
		pen::memory_cpy( (u8*)tcp->data + data_size, ext_image_start, ext_data_size );

		//free the files contents
		pen::memory_free( file_data );

		return tcp;
	}

	void loader_free_texture( pen::texture_creation_params** tcp )
	{
		pen::memory_free( (*tcp)->data );
		pen::memory_free( *tcp );

		*tcp = NULL;
	}

	c8 semantic_names[7][16] =
	{
		"POSITION",
		"TEXCOORD",
		"NORMAL",
		"TANGENT",
		"BITANGENT",
		"COLOR",
		"BLENDINDICES"
	};

	shader_program loader_load_shader_program( const c8* shader_name )
	{
        c8 vs_file_buf[ 256 ];
        c8 ps_file_buf[ 256 ];
        c8 info_file_buf[ 256 ];

        pen::string_format( vs_file_buf, 256, "data/shaders/%s/%s.vsc", pen::renderer_get_shader_platform(), shader_name );
        pen::string_format( ps_file_buf, 256, "data/shaders/%s/%s.psc", pen::renderer_get_shader_platform(), shader_name );
        pen::string_format( info_file_buf, 256, "data/shaders/%s/%s.json", pen::renderer_get_shader_platform(), shader_name);

		//shaders
		pen::shader_load_params vs_slp;
		vs_slp.type = PEN_SHADER_TYPE_VS;

		pen::shader_load_params ps_slp;
		ps_slp.type = PEN_SHADER_TYPE_PS;

		//textured
		u32 err = pen::filesystem_read_file_to_buffer( vs_file_buf, &vs_slp.byte_code, vs_slp.byte_code_size );

        shader_program prog;

		if ( err != PEN_ERR_OK  )
        {
            //we must have a vertex shader, if this has failed, so will have the input layout.
            prog.input_layout = 0;
            prog.vertex_shader = 0;
            prog.pixel_shader = 0;

            return prog;
        }

		//read shader info json
		std::ifstream ifs(info_file_buf);
		json j = json::parse(ifs);

		//create input layout from json
		pen::input_layout_creation_params ilp;
		ilp.vs_byte_code = vs_slp.byte_code;
		ilp.vs_byte_code_size = vs_slp.byte_code_size;
		ilp.num_elements = j["vs_inputs"].size();

		ilp.input_layout = (pen::input_layout_desc*)pen::memory_alloc(sizeof(pen::input_layout_desc) * ilp.num_elements);

		for (u32 i = 0; i < ilp.num_elements; ++i)
		{
			json vj = j["vs_inputs"][i];

			u32 num_elements = vj["num_elements"];
			u32 elements_size = vj["element_size"];

			static const s32 float_formats[4] =
			{
				PEN_VERTEX_FORMAT_FLOAT1,
				PEN_VERTEX_FORMAT_FLOAT2,
				PEN_VERTEX_FORMAT_FLOAT3,
				PEN_VERTEX_FORMAT_FLOAT4
			};

			static const s32 byte_formats[4] =
			{
				PEN_VERTEX_FORMAT_UNORM1,
				PEN_VERTEX_FORMAT_UNORM2,
				PEN_VERTEX_FORMAT_UNORM2,
				PEN_VERTEX_FORMAT_UNORM4
			};

			const s32* fomats = float_formats;

			if (elements_size == 1)
				fomats = byte_formats;

			ilp.input_layout[i].semantic_index = vj["semantic_index"];
			ilp.input_layout[i].format = fomats[num_elements-1];
			ilp.input_layout[i].semantic_name = &semantic_names[vj["semantic_id"]][0];
			ilp.input_layout[i].input_slot = 0;
			ilp.input_layout[i].aligned_byte_offset = vj["offset"];
			ilp.input_layout[i].input_slot_class = PEN_INPUT_PER_VERTEX;
			ilp.input_layout[i].instance_data_step_rate = 0;
		}

		prog.input_layout = pen::defer::renderer_create_input_layout(ilp);

		if ( err != PEN_ERR_OK  )
		{
            //this shader set does not have a pixel shader which is valid, to allow fast z-only writes.
            ps_slp.byte_code = NULL;
            ps_slp.byte_code_size = 0;
		}

        err = pen::filesystem_read_file_to_buffer(ps_file_buf, &ps_slp.byte_code, ps_slp.byte_code_size);

		prog.vertex_shader = pen::defer::renderer_load_shader( vs_slp );
		prog.pixel_shader = pen::defer::renderer_load_shader( ps_slp );
        
        //link the shader to allow opengl to match d3d constant and texture bindings
        pen::shader_link_params link_params;
        link_params.input_layout = prog.input_layout;
        link_params.vertex_shader = prog.vertex_shader;
        link_params.pixel_shader = prog.pixel_shader;
        
        u32 num_constants = j["cbuffers"].size() + j["texture_samplers"].size();
        
        link_params.constants = (pen::constant_layout_desc*)pen::memory_alloc(sizeof(pen::constant_layout_desc) * num_constants);
        
        u32 cc = 0;
        
        for( auto& cbuf : j["cbuffers"])
        {
            std::string name_str = cbuf["name"];
            u32 name_len = name_str.length();
            
            link_params.constants[cc].name = new c8[name_len+1];
            
            pen::memory_cpy(link_params.constants[cc].name, name_str.c_str(), name_len );
            
            link_params.constants[cc].name[name_len] = '\0';
            
            link_params.constants[cc].location = cbuf["location"];
            
            link_params.constants[cc].type = pen::CT_CBUFFER;
            
            cc++;
        }
        
        for( auto& samplers : j["texture_samplers"])
        {
            std::string name_str = samplers["name"];
            u32 name_len = name_str.length();
            
            link_params.constants[cc].name = (c8*)pen::memory_alloc(name_len+1);
            
            pen::memory_cpy(link_params.constants[cc].name, name_str.c_str(), name_len );
            
            link_params.constants[cc].name[name_len] = '\0';
            
            link_params.constants[cc].location = samplers["location"];
            
            static std::string sampler_type_names[] =
            {
                "TEXTURE_2D",
                "TEXTURE_3D",
                "TEXTURE_CUBE"
            };
            
            for( u32 i = 0; i < 3; ++i )
            {
                if( samplers["type"] == sampler_type_names[i] )
                {
                    link_params.constants[cc].type = (pen::constant_type)i;
                    break;
                }
            }

            cc++;
        }
        
        link_params.num_constants = num_constants;
        
        pen::defer::renderer_link_shader_program(link_params);
        
        //free the temp mem
        for( u32 c = 0; c < num_constants; ++c )
        {
            pen::memory_free(link_params.constants[c].name);
        }
        
        pen::memory_free( link_params.constants );
		pen::memory_free( vs_slp.byte_code );
		pen::memory_free( ps_slp.byte_code );
		pen::memory_free( ilp.input_layout );

		return prog;
	}

	skeleton* loader_load_skeleton( const c8* filename )
	{
		void*  skeleton_data;
		u32	   file_size;

		pen::filesystem_read_file_to_buffer( filename, &skeleton_data, file_size );

		u32*	header = (u32*)skeleton_data;

		//alloc a new skeleton
		skeleton* p_skeleton = (skeleton*)pen::memory_alloc(sizeof(skeleton));

		//with number of joints allocate space for parents and transforms
		p_skeleton->num_joints = (u32)header[ 1 ];

		p_skeleton->parents = (u32*)pen::memory_alloc(sizeof(u32)*p_skeleton->num_joints);
		p_skeleton->offsets = (vec3f*)pen::memory_alloc(sizeof(vec3f)*p_skeleton->num_joints);
		p_skeleton->rotations = (Quaternion*)pen::memory_alloc(sizeof(Quaternion)*p_skeleton->num_joints);
		p_skeleton->names = (c8**)pen::memory_alloc(sizeof(c8*)*p_skeleton->num_joints);

		u32* p_int = &header[ 2 ];
		for( u32 i = 0; i < p_skeleton->num_joints; ++i )
		{
			//name
			u32 num_chars = *p_int++;
			p_skeleton->names[ i ] = (c8*)pen::memory_alloc(sizeof(c8)*(num_chars+1));
			
			c8 buf[ 32 ];
			for( u32 c = 0; c < num_chars; ++c)
			{
				if( c >= 32 )
				{
					break;
				}

				buf[ c ] = (c8)*p_int++;
			}

			pen::memory_cpy( &p_skeleton->names[ i ][ 0 ], &buf[ 0 ], num_chars );
			p_skeleton->names[ i ][ num_chars ] = '\0';

			//parent
			p_skeleton->parents[ i ] = *p_int++;

			//num transforms
			u32 num_transforms = *p_int++;

			u32 num_rotations = 0;
			vec4f rotations[ 3 ];

			for( u32 t = 0; t < num_transforms; ++t )
			{
				u32 type = *p_int++;

				if( type == 0 )
				{
					//translate
					pen::memory_set( &p_skeleton->offsets[i], 0xff, 12 );
					pen::memory_cpy( &p_skeleton->offsets[i], p_int, 12 );
					p_int += 3;
				}
				else if( type == 1 )
				{
					//rotate
					pen::memory_cpy( &rotations[ num_rotations ], p_int, 16 );

					//convert to radians
					rotations[ num_rotations ].w = psmath::deg_to_rad( rotations[ num_rotations ].w );

					static f32 zero_rotation_epsilon = 0.000001f;
					if( rotations[ num_rotations ].w < zero_rotation_epsilon && rotations[ num_rotations ].w > zero_rotation_epsilon )
					{
						rotations[ num_rotations ].w = 0.0f;
					}

					num_rotations++;

					p_int += 4;
				}
				else
				{
					//unsupported transform type
					PEN_ASSERT( 0 );
				}
			}

			PEN_ASSERT( num_rotations <= 3 );

			if( num_rotations == 0 )
			{
				//no rotation
				p_skeleton->rotations[ i ].euler_angles( 0.0f, 0.0f, 0.0f );
			}
			else if( num_rotations == 1 )
			{
				//axis angle
				p_skeleton->rotations[ i ].axis_angle( rotations[ 0 ] );
			}
			else if( num_rotations == 3 )
			{
				//euler angles
				f32 z_theta = 0; 
				f32 y_theta = 0; 
				f32 x_theta = 0; 

				for( u32 r = 0; r < 3; ++r )
				{
					if( rotations[r].z == 1.0f )
					{
						z_theta = rotations[r].w;
					}
					else if (rotations[r].y == 1.0f)
					{
						y_theta = rotations[r].w;
					}
					else if (rotations[r].x == 1.0f)
					{
						x_theta = rotations[r].w;
					}

					p_skeleton->rotations[i].euler_angles( z_theta, y_theta, x_theta );
				}
			}
		}

		//animations
		p_skeleton->num_anims = *p_int++;

		p_skeleton->animations = (animation*)pen::memory_alloc( sizeof(animation)*p_skeleton->num_anims  );

		vec3f anim_val;
		for( u32 a = 0; a < p_skeleton->num_anims ; a++ )
		{
			p_skeleton->animations[a].bone_index = *p_int++;
			p_skeleton->animations[a].num_times = *p_int++;

			p_skeleton->animations[a].rotations = NULL;
			p_skeleton->animations[a].translations = NULL;

			u32 num_translations = *p_int++;
			u32 num_rotations = *p_int++;

			p_skeleton->animations[a].timeline = (f32*)pen::memory_alloc( sizeof(f32)*p_skeleton->animations[a].num_times );

			if (num_translations == p_skeleton->animations[a].num_times)
			{
				p_skeleton->animations[a].translations = (vec3f*)pen::memory_alloc( sizeof(vec3f)*num_translations );
			}

			if (num_rotations == p_skeleton->animations[a].num_times)
			{
				p_skeleton->animations[a].rotations = (Quaternion*)pen::memory_alloc( sizeof(Quaternion)*num_rotations );
				p_skeleton->animations[a].euler_angles = (vec3f*)pen::memory_alloc( sizeof(vec3f)*num_rotations );
			}

			for (u32 t = 0; t < p_skeleton->animations[a].num_times; ++t)
			{
				pen::memory_cpy( &p_skeleton->animations[a].timeline[t], p_int, 4 );
				p_int++;

				if (p_skeleton->animations[a].translations)
				{
					pen::memory_cpy( &p_skeleton->animations[a].translations[t], p_int, 12 );
					p_int += 3;
				}

				if (p_skeleton->animations[a].rotations)
				{
					vec3f euler_angs;
					pen::memory_cpy( &euler_angs, p_int, 12 );

					if( vec3f::almost_equal( euler_angs, vec3f::zero() ) )
					{
						euler_angs = vec3f::zero();
					}

					pen::memory_cpy( &p_skeleton->animations[a].euler_angles[t], &euler_angs, 12 );
					
					p_skeleton->animations[a].rotations[t].euler_angles( psmath::deg_to_rad( euler_angs.z ), psmath::deg_to_rad( euler_angs.y ), psmath::deg_to_rad( euler_angs.x ) );
					p_int += 3;
				}
			}
		}

		pen::memory_free( skeleton_data );

		return p_skeleton;
	}
}
