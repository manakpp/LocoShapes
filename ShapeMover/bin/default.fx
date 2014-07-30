float4x4 gWorld;
float4x4 gView;
float4x4 gProjection;
 
struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
};
 
PS_INPUT VS(float4 _pos : POSITION, float4 _color : COLOR )
{
    PS_INPUT psInput;
 
    _pos = mul(_pos, gWorld);
    _pos = mul(_pos, gView);
 
    psInput.pos = mul(_pos, gProjection);
    psInput.color = _color;
 
    return psInput;
}
 
float4 PS( PS_INPUT _psInput ) : SV_Target
{
    return _psInput.color;
}
 
technique10 DefaultTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}