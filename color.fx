//=============================================================================
// color.fx by Frank Luna (C) 2008 All Rights Reserved.
//
// Transforms and colors geometry.
//=============================================================================

cbuffer cbPerObject
{
	float4x4 gWVP; 
	int mode;
	float diff;
};

void VS(float3 iPosL  : POSITION,
        float4 iColor : COLOR,
        out float4 oPosH  : SV_POSITION,
        out float4 oColor : COLOR)
{
	// Transform to homogeneous clip space.
	oPosH = mul(float4(iPosL, 1.0f), gWVP);

	switch(mode) {
	case 0:		// Player
		oColor = float4(0.0f, 0.0f, 1.0f, 1.0f);	// Blue
		break;
	case 1:
		oColor = float4(0.4f, 0.8f, 1.0f, .5f); // invulnerable color
		break;
	default:
		oColor = iColor;	// Red
		break;
	}

	//oColor = iColor;
	
}

float4 PS(float4 posH  : SV_POSITION,
          float4 color : COLOR) : SV_Target
{
    return color;
}

technique10 ColorTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
