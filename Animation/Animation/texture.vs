cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexType
{
	float4 position: POSITION;
	float2 tex: TEXCOORD0;
	float2 boneIDS : BONEIDS;

};

struct PixelType
{
	float4 position: SV_POSITION;
	float2 tex: TEXCOORD0;

};

PixelType VertexTextureShader(VertexType input)
{
	PixelType output;

	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;

	return output;
}