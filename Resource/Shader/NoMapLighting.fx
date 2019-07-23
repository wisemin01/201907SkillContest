struct VS_INPUT
{
	float4 mPosition	: POSITION;
	float3 mNormal		: NORMAL;
};

struct VS_OUTPUT
{
	float4 mPosition	: POSITION;
	float3 mDiffuse		: TEXCOORD1;
	float3 mReflect		: TEXCOORD2;
	float3 mViewDir		: TEXCOORD3;
};

float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjMatrix;

float4 gWorldLight = float4(500, 500, 500, 1);
float4 gWorldCamera;
float3 gLightingColor = float3(0.5, 0.5, 0.8);


VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, gWorldMatrix);

	float3 worldNormal = normalize(mul(Input.mNormal, (float3x3)gWorldMatrix));
	float3 lightDir = normalize(Output.mPosition.xyz - gWorldLight.xyz);
	float3 viewDir = normalize(Output.mPosition.xyz - gWorldCamera.xyz);

	Output.mDiffuse = dot(worldNormal, -lightDir);
	Output.mReflect = reflect(lightDir, worldNormal);
	Output.mViewDir = viewDir;

	Output.mPosition = mul(Output.mPosition, gViewMatrix);
	Output.mPosition = mul(Output.mPosition, gProjMatrix);

	return Output;
}

struct PS_INPUT
{
	float3 mDiffuse		: TEXCOORD1;
	float3 mReflect		: TEXCOORD2;
	float3 mViewDir		: TEXCOORD3;
};


float4 ps_main(PS_INPUT Input) : COLOR
{
	float3 diffuse = saturate(Input.mDiffuse) * gLightingColor;
	float3 specular = 0;
	float3 ambient = 0.1;

	float3 viewDir = normalize(Input.mViewDir);
	float3 reflectDir = normalize(Input.mReflect);

	if (diffuse.x > 0)
	{
		specular = saturate(dot(reflectDir, -viewDir));
		specular = pow(specular, 20.f) * gLightingColor;
	}

	return float4((ambient + diffuse + specular), 1);
}

technique Color
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}
