/*
 *	@File	Animation2DSprite.cpp
 *	@Brief	2D�X�v���C�g�̃A�j���[�V�����N���X�B
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Animation2DSprite.h"

constexpr auto PLAYER_TEXTURE_PATH = L"Resources/Textures/Editor/Buttons/LoadButton.dds";

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Animation2DSprite::Animation2DSprite()
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Animation2DSprite::~Animation2DSprite()
{
}

//==============================================================================
// ���\�[�X�̍쐬
//==============================================================================
void Animation2DSprite::CreateResources()
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	m_batch = std::make_unique<PrimitiveVertex>(_context);
	m_states = std::make_unique<CommonStates>(_device);
	m_shaders = std::make_unique<Shaders>();

	// �V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _tex;

	// �t�@�C���ǂݍ���
	CreateDDSTextureFromFile(_device, PLAYER_TEXTURE_PATH, nullptr, m_srv.ReleaseAndGetAddressOf());
}

//==============================================================================
// �`��֐�
//==============================================================================
void Animation2DSprite::Draw()
{

}

//==============================================================================
// Name
//==============================================================================
void Animation2DSprite::CreateBillboard(SimpleMath::Vector3 eye, SimpleMath::Vector3 target, SimpleMath::Vector3 up)
{
	m_world = SimpleMath::Matrix::CreateBillboard(SimpleMath::Vector3::Zero, eye - target, up);

	// ��]���~�߂ď�ɐ��ʂɌ�����
	SimpleMath::Matrix _rot = SimpleMath::Matrix::Identity;
	_rot._11 = -1;
	_rot._33 = -1;

	m_cameraPosition = eye;
	m_cameraTarget = target;

	// �r���{�[�h�̃e�N�X�`������]
	m_world = _rot * m_world;
}

//==============================================================================
// �R���X�^���g�o�b�t�@�̍쐬
//==============================================================================
void Animation2DSprite::CreateConstBuffer()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �R���X�^���g�o�b�t�@��`
	D3D11_BUFFER_DESC _buffer = {};

	// ���g����ɂ���
	ZeroMemory(&_buffer, sizeof(_buffer));

	// �ǂݏ����̃��[�h���f�t�H���g�ɂ���
	_buffer.Usage = D3D11_USAGE_DEFAULT;

	// �V�F�[�_�[�Ŏg���f�[�^�\���̂̃T�C�Y���i�[
	_buffer.ByteWidth = sizeof(ConstBuffer);

	// �o�b�t�@�[��萔�o�b�t�@�[�Ƃ��ĕR�Â���
	_buffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// CPU���珑���������ł��Ȃ�����
	_buffer.CPUAccessFlags = NULL;

	// �쐬�����o�b�t�@���i�[
	_device->CreateBuffer(&_buffer, nullptr, &m_buffer);
}

