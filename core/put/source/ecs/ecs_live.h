// codegen_2
#pragma once
#include "ecs_scene.h"
#include "ecs_resources.h"
#include "ecs_utilities.h"
#include "debug_render.h"
namespace put {
    namespace ecs{
        typedef ecs_scene* (*proc_create_scene)(const c8*);
        typedef void (*proc_destroy_scene)(ecs_scene*);
        typedef ecs_scene_list* (*proc_get_scenes)(void);
        typedef void (*proc_update)(f32);
        typedef void (*proc_update_scene)(ecs_scene*, f32);
        typedef void (*proc_render_scene_view)(const scene_view&);
        typedef void (*proc_render_light_volumes)(const scene_view&);
        typedef void (*proc_render_shadow_views)(const scene_view&);
        typedef void (*proc_render_omni_shadow_views)(const scene_view&);
        typedef void (*proc_render_area_light_textures)(const scene_view&);
        typedef void (*proc_clear_scene)(ecs_scene*);
        typedef void (*proc_default_scene)(ecs_scene*);
        typedef void (*proc_resize_scene_buffers)(ecs_scene*, s32);
        typedef void (*proc_zero_entity_components)(ecs_scene*, u32);
        typedef void (*proc_delete_entity)(ecs_scene*, u32);
        typedef void (*proc_delete_entity_first_pass)(ecs_scene*, u32);
        typedef void (*proc_delete_entity_second_pass)(ecs_scene*, u32);
        typedef void (*proc_initialise_free_list)(ecs_scene*);
        typedef void (*proc_register_ecs_extentsions)(ecs_scene*, const ecs_extension&);
        typedef void (*proc_unregister_ecs_extensions)(ecs_scene*);
        typedef void (*proc_register_ecs_controller)(ecs_scene*, const ecs_controller&);
        typedef  u32 (*proc_get_extension_component_offset)(ecs_scene*, u32);
        typedef  u32 (*proc_get_extension_component_offset_from_id)(ecs_scene*, hash_id);
        typedef void (*proc_save_scene)(const c8*, ecs_scene*);
        typedef void (*proc_save_sub_scene)(ecs_scene*, u32);
        typedef void (*proc_load_scene)(const c8*, ecs_scene*, bool);
        typedef s32 (*proc_load_pmm)(const c8*, ecs_scene*, u32);
        typedef s32 (*proc_load_pma)(const c8*);
        typedef s32 (*proc_load_pmv)(const c8*, ecs_scene*);
        typedef void (*proc_optimise_pmm)(const c8*, const c8*);
        typedef void (*proc_optimise_pma)(const c8*, const c8*);
        typedef void (*proc_instantiate_rigid_body)(ecs_scene*, u32);
        typedef void (*proc_instantiate_compound_rigid_body)(ecs_scene*, u32, u32*, u32);
        typedef void (*proc_instantiate_constraint)(ecs_scene*, u32);
        typedef void (*proc_instantiate_geometry)(geometry_resource*, ecs_scene*, s32);
        typedef void (*proc_instantiate_model_pre_skin)(ecs_scene*, s32);
        typedef void (*proc_instantiate_model_cbuffer)(ecs_scene*, s32);
        typedef void (*proc_instantiate_material_cbuffer)(ecs_scene*, s32, s32);
        typedef void (*proc_instantiate_anim_controller_v2)(ecs_scene*, s32);
        typedef void (*proc_instantiate_material)(material_resource*, ecs_scene*, u32);
        typedef void (*proc_instantiate_sdf_shadow)(const c8*, ecs_scene*, u32);
        typedef void (*proc_instantiate_light)(ecs_scene*, u32);
        typedef void (*proc_instantiate_area_light)(ecs_scene*, u32);
        typedef void (*proc_instantiate_area_light_ex)(ecs_scene*, u32, area_light_resource&);
        typedef void (*proc_destroy_geometry)(ecs_scene*, u32);
        typedef void (*proc_destroy_physics)(ecs_scene*, s32);
        typedef void (*proc_bake_rigid_body_params)(ecs_scene*, u32);
        typedef void (*proc_bake_material_handles)(ecs_scene*, u32);
        typedef void (*proc_create_geometry_primitives)(void);
        typedef void (*proc_add_geometry_resource)(geometry_resource*);
        typedef void (*proc_add_material_resource)(material_resource*);
        typedef material_resource* (*proc_get_material_resource)(hash_id);
        typedef animation_resource* (*proc_get_animation_resource)(anim_handle);
        typedef geometry_resource* (*proc_get_geometry_resource)(hash_id);
        typedef geometry_resource* (*proc_get_geometry_resource_by_index)(hash_id, u32);
        typedef u32 (*proc_get_next_entity)(ecs_scene*);
        typedef u32 (*proc_get_new_entity)(ecs_scene*);
        typedef void (*proc_get_new_entities_contiguous)(ecs_scene*, s32, s32&, s32&);
        typedef void (*proc_get_new_entities_append)(ecs_scene*, s32, s32&, s32&);
        typedef u32 (*proc_clone_entity)(ecs_scene*, u32, s32, s32, clone_mode, vec3f, const c8*);
        typedef void (*proc_swap_entities)(ecs_scene*, u32, s32);
        typedef void (*proc_clone_selection_hierarchical)(ecs_scene*, u32**, const c8*);
        typedef void (*proc_instance_entity_range)(ecs_scene*, u32, u32);
        typedef void (*proc_bake_entities_to_vb)(ecs_scene*, u32, u32*);
        typedef void (*proc_set_entity_parent)(ecs_scene*, u32, u32);
        typedef void (*proc_set_entity_parent_validate)(ecs_scene*, u32&, u32&);
        typedef void (*proc_trim_entities)(ecs_scene*);
        typedef u32 (*proc_bind_animation_to_rig)(ecs_scene*, anim_handle, u32);
        typedef void (*proc_tree_to_entity_index_list)(const scene_tree&, s32, std::vector<s32>&);
        typedef void (*proc_build_scene_tree)(ecs_scene*, s32, scene_tree&);
        typedef void (*proc_build_heirarchy_node_list)(ecs_scene*, s32, std::vector<s32>&);
        typedef void (*proc_scene_tree_enumerate)(ecs_scene*, const scene_tree&);
        typedef void (*proc_scene_tree_add_entity)(scene_tree&, scene_tree&, std::vector<s32>&);
        typedef Str (*proc_read_parsable_string)(const u32**);
        typedef void (*proc_write_parsable_string)(const Str&, std::ofstream&);
        typedef void (*proc_write_parsable_string_u32)(const Str&, std::ofstream&);
        struct __ecs {
            void* __ecs_start;
            proc_create_scene create_scene;
            proc_destroy_scene destroy_scene;
            proc_get_scenes get_scenes;
            proc_update update;
            proc_update_scene update_scene;
            proc_render_scene_view render_scene_view;
            proc_render_light_volumes render_light_volumes;
            proc_render_shadow_views render_shadow_views;
            proc_render_omni_shadow_views render_omni_shadow_views;
            proc_render_area_light_textures render_area_light_textures;
            proc_clear_scene clear_scene;
            proc_default_scene default_scene;
            proc_resize_scene_buffers resize_scene_buffers;
            proc_zero_entity_components zero_entity_components;
            proc_delete_entity delete_entity;
            proc_delete_entity_first_pass delete_entity_first_pass;
            proc_delete_entity_second_pass delete_entity_second_pass;
            proc_initialise_free_list initialise_free_list;
            proc_register_ecs_extentsions register_ecs_extentsions;
            proc_unregister_ecs_extensions unregister_ecs_extensions;
            proc_register_ecs_controller register_ecs_controller;
            proc_get_extension_component_offset get_extension_component_offset;
            proc_get_extension_component_offset_from_id get_extension_component_offset_from_id;
            proc_save_scene save_scene;
            proc_save_sub_scene save_sub_scene;
            proc_load_scene load_scene;
            proc_load_pmm load_pmm;
            proc_load_pma load_pma;
            proc_load_pmv load_pmv;
            proc_optimise_pmm optimise_pmm;
            proc_optimise_pma optimise_pma;
            proc_instantiate_rigid_body instantiate_rigid_body;
            proc_instantiate_compound_rigid_body instantiate_compound_rigid_body;
            proc_instantiate_constraint instantiate_constraint;
            proc_instantiate_geometry instantiate_geometry;
            proc_instantiate_model_pre_skin instantiate_model_pre_skin;
            proc_instantiate_model_cbuffer instantiate_model_cbuffer;
            proc_instantiate_material_cbuffer instantiate_material_cbuffer;
            proc_instantiate_anim_controller_v2 instantiate_anim_controller_v2;
            proc_instantiate_material instantiate_material;
            proc_instantiate_sdf_shadow instantiate_sdf_shadow;
            proc_instantiate_light instantiate_light;
            proc_instantiate_area_light instantiate_area_light;
            proc_instantiate_area_light_ex instantiate_area_light_ex;
            proc_destroy_geometry destroy_geometry;
            proc_destroy_physics destroy_physics;
            proc_bake_rigid_body_params bake_rigid_body_params;
            proc_bake_material_handles bake_material_handles;
            proc_create_geometry_primitives create_geometry_primitives;
            proc_add_geometry_resource add_geometry_resource;
            proc_add_material_resource add_material_resource;
            proc_get_material_resource get_material_resource;
            proc_get_animation_resource get_animation_resource;
            proc_get_geometry_resource get_geometry_resource;
            proc_get_geometry_resource_by_index get_geometry_resource_by_index;
            proc_get_next_entity get_next_entity;
            proc_get_new_entity get_new_entity;
            proc_get_new_entities_contiguous get_new_entities_contiguous;
            proc_get_new_entities_append get_new_entities_append;
            proc_clone_entity clone_entity;
            proc_swap_entities swap_entities;
            proc_clone_selection_hierarchical clone_selection_hierarchical;
            proc_instance_entity_range instance_entity_range;
            proc_bake_entities_to_vb bake_entities_to_vb;
            proc_set_entity_parent set_entity_parent;
            proc_set_entity_parent_validate set_entity_parent_validate;
            proc_trim_entities trim_entities;
            proc_bind_animation_to_rig bind_animation_to_rig;
            proc_tree_to_entity_index_list tree_to_entity_index_list;
            proc_build_scene_tree build_scene_tree;
            proc_build_heirarchy_node_list build_heirarchy_node_list;
            proc_scene_tree_enumerate scene_tree_enumerate;
            proc_scene_tree_add_entity scene_tree_add_entity;
            proc_read_parsable_string read_parsable_string;
            proc_write_parsable_string write_parsable_string;
            proc_write_parsable_string_u32 write_parsable_string_u32;
            void* __ecs_end;
        };

        #if !DLL
        void generate_bindings(__ecs* ctx){
            ctx->create_scene = &create_scene;
            ctx->destroy_scene = &destroy_scene;
            ctx->get_scenes = &get_scenes;
            ctx->update = &update;
            ctx->update_scene = &update_scene;
            ctx->render_scene_view = &render_scene_view;
            ctx->render_light_volumes = &render_light_volumes;
            ctx->render_shadow_views = &render_shadow_views;
            ctx->render_omni_shadow_views = &render_omni_shadow_views;
            ctx->render_area_light_textures = &render_area_light_textures;
            ctx->clear_scene = &clear_scene;
            ctx->default_scene = &default_scene;
            ctx->resize_scene_buffers = &resize_scene_buffers;
            ctx->zero_entity_components = &zero_entity_components;
            ctx->delete_entity = &delete_entity;
            ctx->delete_entity_first_pass = &delete_entity_first_pass;
            ctx->delete_entity_second_pass = &delete_entity_second_pass;
            ctx->initialise_free_list = &initialise_free_list;
            ctx->register_ecs_extentsions = &register_ecs_extentsions;
            ctx->unregister_ecs_extensions = &unregister_ecs_extensions;
            ctx->register_ecs_controller = &register_ecs_controller;
            ctx->get_extension_component_offset = &get_extension_component_offset;
            ctx->get_extension_component_offset_from_id = &get_extension_component_offset_from_id;
            ctx->save_scene = &save_scene;
            ctx->save_sub_scene = &save_sub_scene;
            ctx->load_scene = &load_scene;
            ctx->load_pmm = &load_pmm;
            ctx->load_pma = &load_pma;
            ctx->load_pmv = &load_pmv;
            ctx->optimise_pmm = &optimise_pmm;
            ctx->optimise_pma = &optimise_pma;
            ctx->instantiate_rigid_body = &instantiate_rigid_body;
            ctx->instantiate_compound_rigid_body = &instantiate_compound_rigid_body;
            ctx->instantiate_constraint = &instantiate_constraint;
            ctx->instantiate_geometry = &instantiate_geometry;
            ctx->instantiate_model_pre_skin = &instantiate_model_pre_skin;
            ctx->instantiate_model_cbuffer = &instantiate_model_cbuffer;
            ctx->instantiate_material_cbuffer = &instantiate_material_cbuffer;
            ctx->instantiate_anim_controller_v2 = &instantiate_anim_controller_v2;
            ctx->instantiate_material = &instantiate_material;
            ctx->instantiate_sdf_shadow = &instantiate_sdf_shadow;
            ctx->instantiate_light = &instantiate_light;
            ctx->instantiate_area_light = &instantiate_area_light;
            ctx->instantiate_area_light_ex = &instantiate_area_light_ex;
            ctx->destroy_geometry = &destroy_geometry;
            ctx->destroy_physics = &destroy_physics;
            ctx->bake_rigid_body_params = &bake_rigid_body_params;
            ctx->bake_material_handles = &bake_material_handles;
            ctx->create_geometry_primitives = &create_geometry_primitives;
            ctx->add_geometry_resource = &add_geometry_resource;
            ctx->add_material_resource = &add_material_resource;
            ctx->get_material_resource = &get_material_resource;
            ctx->get_animation_resource = &get_animation_resource;
            ctx->get_geometry_resource = &get_geometry_resource;
            ctx->get_geometry_resource_by_index = &get_geometry_resource_by_index;
            ctx->get_next_entity = &get_next_entity;
            ctx->get_new_entity = &get_new_entity;
            ctx->get_new_entities_contiguous = &get_new_entities_contiguous;
            ctx->get_new_entities_append = &get_new_entities_append;
            ctx->clone_entity = &clone_entity;
            ctx->swap_entities = &swap_entities;
            ctx->clone_selection_hierarchical = &clone_selection_hierarchical;
            ctx->instance_entity_range = &instance_entity_range;
            ctx->bake_entities_to_vb = &bake_entities_to_vb;
            ctx->set_entity_parent = &set_entity_parent;
            ctx->set_entity_parent_validate = &set_entity_parent_validate;
            ctx->trim_entities = &trim_entities;
            ctx->bind_animation_to_rig = &bind_animation_to_rig;
            ctx->tree_to_entity_index_list = &tree_to_entity_index_list;
            ctx->build_scene_tree = &build_scene_tree;
            ctx->build_heirarchy_node_list = &build_heirarchy_node_list;
            ctx->scene_tree_enumerate = &scene_tree_enumerate;
            ctx->scene_tree_add_entity = &scene_tree_add_entity;
            ctx->read_parsable_string = &read_parsable_string;
            ctx->write_parsable_string = &write_parsable_string;
            ctx->write_parsable_string_u32 = &write_parsable_string_u32;
        }

        #endif
    }

    namespace dbg{
        typedef void (*proc_init)(void);
        typedef void (*proc_shutdown)(void);
        typedef void (*proc_add_line)(const vec3f&, const vec3f&, const vec4f&);
        typedef void (*proc_add_coord_space)(const mat4&, const f32, u32);
        typedef void (*proc_add_point)(const vec3f&, f32, const vec4f&);
        typedef void (*proc_add_grid)(const vec3f&, const vec3f&, const vec3f&);
        typedef void (*proc_add_aabb)(const vec3f&, const vec3f&, const vec4f&);
        typedef void (*proc_add_circle)(const vec3f&, const vec3f&, f32, const vec4f&);
        typedef void (*proc_add_circle_segment)(const vec3f&, const vec3f&, f32, f32, f32, const vec4f&);
        typedef void (*proc_add_frustum)(const vec3f*, const vec3f*, const vec4f&);
        typedef void (*proc_add_triangle)(const vec3f&, const vec3f&, const vec3f&, const vec4f&);
        typedef void (*proc_add_triangle_with_normal)(const vec3f&, const vec3f&, const vec3f&, const vec4f&);
        typedef void (*proc_add_plane)(const vec3f&, const vec3f&, f32, vec4f);
        typedef void (*proc_add_obb)(const mat4&, vec4f);
        typedef void (*proc_add_line_2f)(const vec2f&, const vec2f&, const vec4f&);
        typedef void (*proc_add_point_2f)(const vec2f&, const vec4f&);
        typedef void (*proc_add_quad_2f)(const vec2f&, const vec2f&, const vec4f&);
        typedef void (*proc_add_tri_2f)(const vec2f&, const vec2f&, const vec2f&, const vec4f&);
        typedef void (*proc_add_text_2f)(const f32, const f32, const pen::viewport&, const vec4f&, const c8*, ...);
        typedef void (*proc_add_axis_transform_widget)(const mat4&, const f32, u32, u32, const mat4&, const mat4&, const vec2i&);
        typedef void (*proc_render_2d)(u32);
        typedef void (*proc_render_3d)(u32);
        struct __dbg {
            void* __dbg_start;
            proc_init init;
            proc_shutdown shutdown;
            proc_add_line add_line;
            proc_add_coord_space add_coord_space;
            proc_add_point add_point;
            proc_add_grid add_grid;
            proc_add_aabb add_aabb;
            proc_add_circle add_circle;
            proc_add_circle_segment add_circle_segment;
            proc_add_frustum add_frustum;
            proc_add_triangle add_triangle;
            proc_add_triangle_with_normal add_triangle_with_normal;
            proc_add_plane add_plane;
            proc_add_obb add_obb;
            proc_add_line_2f add_line_2f;
            proc_add_point_2f add_point_2f;
            proc_add_quad_2f add_quad_2f;
            proc_add_tri_2f add_tri_2f;
            proc_add_text_2f add_text_2f;
            proc_add_axis_transform_widget add_axis_transform_widget;
            proc_render_2d render_2d;
            proc_render_3d render_3d;
            void* __dbg_end;
        };

        #if !DLL
        void generate_bindings(__dbg* ctx){
            ctx->init = &init;
            ctx->shutdown = &shutdown;
            ctx->add_line = &add_line;
            ctx->add_coord_space = &add_coord_space;
            ctx->add_point = &add_point;
            ctx->add_grid = &add_grid;
            ctx->add_aabb = &add_aabb;
            ctx->add_circle = &add_circle;
            ctx->add_circle_segment = &add_circle_segment;
            ctx->add_frustum = &add_frustum;
            ctx->add_triangle = &add_triangle;
            ctx->add_triangle_with_normal = &add_triangle_with_normal;
            ctx->add_plane = &add_plane;
            ctx->add_obb = &add_obb;
            ctx->add_line_2f = &add_line_2f;
            ctx->add_point_2f = &add_point_2f;
            ctx->add_quad_2f = &add_quad_2f;
            ctx->add_tri_2f = &add_tri_2f;
            ctx->add_text_2f = &add_text_2f;
            ctx->add_axis_transform_widget = &add_axis_transform_widget;
            ctx->render_2d = &render_2d;
            ctx->render_3d = &render_3d;
        }

        #endif
    }

    struct live_context {
        pen::render_ctx render;
        ecs::ecs_scene* scene;
        ecs::__ecs* ecs_funcs;
        dbg::__dbg* dbg_funcs;
    };
}
