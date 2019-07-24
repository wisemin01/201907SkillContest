struct VS_INPUT
{
	float4 mPosition : POSITION;
	float3 mNormal : NORMAL;
	float2 mUv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition : POSITION;
	float2 mUv : TEXCOORD0;

	float3 mDiffuse : TEXCOORD1;
	float3 mViewDir : TEXCOORD2;
	float3 mReflect : TEXCOORD3;
};

float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjMatrix;

float3 gCameraPos;
float3 gLightPos;
float3 gAmbient;

VS_OUTPUT vs_main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.mPosition = mul(input.mPosition, gWorldMatrix);

	float3 worldNormal = normalize(mul(input.mNormal, (float3x3)gWorldMatrix));
	float3 worldLight = normalize(output.mPosition.xyz - gLightPos);
	
	output.mUv = input.mUv;
	output.mDiffuse = dot(worldNormal, -worldLight);
	output.mViewDir = normalize(output.mPosition.xyz - gCameraPos);
	output.mReflect = reflect(worldLight, worldNormal);


	output.mPosition = mul(output.mPosition, gViewMatrix);
	output.mPosition = mul(output.mPosition, gProjMatrix);

	return output;
}


texture gDiffuseMap;
sampler gDiffuseMapSampler = sampler_state
{
	Texture = (gDiffuseMap);
};

texture gSpecularMap;
sampler gSpecularMapSampler = sampler_state
{
	Texture = (gSpecularMap);
};

struct PS_INPUT
{
	float2 mUv : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
	float3 mViewDir : TEXCOORD2;
	float3 mReflect : TEXCOORD3;
};

float4 ps_main(PS_INPUT input) : COLOR
{
	float3 DiffuseAlbedo = tex2D(gDiffuseMapSampler, input.mUv);
	float3 DiffuseLight = DiffuseAlbedo * saturate(input.mDiffuse);

	float3 AmgentDiffuse = DiffuseAlbedo * gAmbient;

	return float4(AmgentDiffuse + DiffuseLight, 1.f);
}


technique Color
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}