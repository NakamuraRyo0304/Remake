struct Input
{
    float4 PositionPS : SV_Position;
};

float4 main(Input pin) : SV_TARGET0
{
    // Z値を出力する
    return pin.PositionPS.z;
}
