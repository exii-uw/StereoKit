const char* sk_shader_builtin_unlit = R"_(
// [name] sk/unlit
cbuffer GlobalBuffer : register(b0) {
	float4x4 sk_view[2];
	float4x4 sk_proj[2];
	float4x4 sk_viewproj[2];
	float4   sk_lighting_sh[9];
	float4   sk_camera_pos[2];
	float4   sk_camera_dir[2];
	float4   sk_fingertip[2];
	float    sk_time;
};
struct Inst {
	float4x4 world;
	float4   color;
	uint     view_id;
};
cbuffer TransformBuffer : register(b1) {
	Inst sk_inst[682];
};
cbuffer ParamBuffer : register(b2) {
	// [ param ] vector color {1, 1, 1, 1} tags { data for whatever! }
	float4 _color;
};
struct vsIn {
	float4 pos  : SV_POSITION;
	float4 col  : COLOR;
	float2 uv   : TEXCOORD0;
};
struct psIn {
	float4 pos   : SV_POSITION;
	float4 color : COLOR0;
	float2 uv    : TEXCOORD0;
	uint view_id : SV_RenderTargetArrayIndex;
};

// [texture] diffuse white
Texture2D tex : register(t0);
SamplerState tex_sampler;

psIn vs(vsIn input, uint id : SV_InstanceID) {
	psIn output;
	float3 world = mul(float4(input.pos.xyz, 1), sk_inst[id].world).xyz;
	output.pos   = mul(float4(world, 1), sk_viewproj[sk_inst[id].view_id]);

	output.view_id = sk_inst[id].view_id;
	output.uv      = input.uv;
	output.color   = input.col * _color * sk_inst[id].color;
	return output;
}
float4 ps(psIn input) : SV_TARGET {
	float4 col   = tex.Sample(tex_sampler, input.uv);
	clip(col.a-0.01);

	col = col * input.color;

	return col; 
})_";