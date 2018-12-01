struct forward_lit
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float3 m_padding;
};

struct forward_lit_skinned
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float3 m_padding;
};

struct forward_lit_instanced
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float3 m_padding;
};

struct forward_lit_instanced_skinned
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float3 m_padding;
};

struct forward_lit_uv_scale
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
};

struct forward_lit_uv_scale_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
};

struct forward_lit_uv_scale_instanced
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
};

struct forward_lit_uv_scale_instanced_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
};

struct forward_lit_sss
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float2 m_padding;
};

struct forward_lit_sss_skinned
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float2 m_padding;
};

struct forward_lit_sss_instanced
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float2 m_padding;
};

struct forward_lit_sss_instanced_skinned
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float2 m_padding;
};

struct forward_lit_sss_uv_scale
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float4 m_padding;
};

struct forward_lit_sss_uv_scale_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float4 m_padding;
};

struct forward_lit_sss_uv_scale_instanced
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float4 m_padding;
};

struct forward_lit_sss_uv_scale_instanced_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float4 m_padding;
};

struct forward_lit_sdf_shadow
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_surface_offset;
	float2 m_padding;
};

struct forward_lit_sdf_shadow_skinned
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_surface_offset;
	float2 m_padding;
};

struct forward_lit_sdf_shadow_instanced
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_surface_offset;
	float2 m_padding;
};

struct forward_lit_sdf_shadow_instanced_skinned
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_surface_offset;
	float2 m_padding;
};

struct forward_lit_sdf_shadow_uv_scale
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_surface_offset;
	float4 m_padding;
};

struct forward_lit_sdf_shadow_uv_scale_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_surface_offset;
	float4 m_padding;
};

struct forward_lit_sdf_shadow_uv_scale_instanced
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_surface_offset;
	float4 m_padding;
};

struct forward_lit_sdf_shadow_uv_scale_instanced_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_surface_offset;
	float4 m_padding;
};

struct forward_lit_sdf_shadow_sss
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
};

struct forward_lit_sdf_shadow_sss_skinned
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
};

struct forward_lit_sdf_shadow_sss_instanced
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
};

struct forward_lit_sdf_shadow_sss_instanced_skinned
{
	float4 m_albedo;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
};

struct forward_lit_sdf_shadow_sss_uv_scale
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct forward_lit_sdf_shadow_sss_uv_scale_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct forward_lit_sdf_shadow_sss_uv_scale_instanced
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct forward_lit_sdf_shadow_sss_uv_scale_instanced_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct gbuffer
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct gbuffer_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct gbuffer_instanced
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct gbuffer_instanced_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct gbuffer_uv_scale
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct gbuffer_uv_scale_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct gbuffer_uv_scale_instanced
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

struct gbuffer_uv_scale_instanced_skinned
{
	float4 m_albedo;
	float2 m_uv_scale;
	float m_roughness;
	float m_reflectivity;
	float m_sss_scale;
	float m_surface_offset;
	float3 m_padding;
};

