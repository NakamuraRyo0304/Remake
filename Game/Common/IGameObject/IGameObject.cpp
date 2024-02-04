/*
 *	@File	IGameObject.cpp
 *	@Brief	�Q�[���I�u�W�F�N�g�B
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/Factories/ModelFactory.h"
#include "IGameObject.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
IGameObject::IGameObject(const wchar_t* path, const wchar_t* dpath, SimpleMath::Vector3 pos)
	: m_world{}						// ���[���h�s��
	, m_parentMatrix{}				// �e���[���h�s��
	, m_position{ pos }				// ���W
	, m_initialPosition{ pos }		// �������W
	, m_scale{}						// �X�P�[��
	, m_initialScale{}				// �����X�P�[��
	, m_rotate{}					// ��]
	, m_filePath{ path }			// ���f���p�X
	, m_directoryPath{ dpath }		// �f�B���N�g���p�X
	, m_id{ ID::Default }			// �I�u�W�F�N�gID
	, m_weight{}					// �I�u�W�F�N�g�̏d��
{
	m_world = SimpleMath::Matrix::Identity;
	m_parentMatrix = SimpleMath::Matrix::Identity;
	m_id = ID::Default;
	m_weight = NON_WEIGHT;
	CreateWorldMatrix();
}

//==============================================================================
// ���[���h�}�g���N�X���쐬
//==============================================================================
void IGameObject::CreateWorldMatrix()
{
	// �X�P�[����ύX
	SimpleMath::Matrix _scale =
		SimpleMath::Matrix::CreateScale(GetScale());
	// ��]��ύX
	SimpleMath::Matrix _rotate =
		SimpleMath::Matrix::CreateFromYawPitchRoll(GetRotate());
	// ���W��ύX
	SimpleMath::Matrix _trans =
		SimpleMath::Matrix::CreateTranslation(GetPosition());

	// �ύX�����f�[�^�𔽉f
	m_world = _scale * _rotate * _trans;
}

//==============================================================================
// ���f�����쐬����
//==============================================================================
void IGameObject::CreateModel()
{
	m_model = ModelFactory::CreateModel(m_filePath, m_directoryPath);
}

//==============================================================================
// ���f����j������
//==============================================================================
void IGameObject::ReleaseModel()
{
	m_model.reset();
	m_VS.Reset();
	m_PS.Reset();
	m_GS.Reset();
}

//==============================================================================
// ���f����ύX����
//==============================================================================
void IGameObject::ChangeModel(const wchar_t* path)
{
	m_filePath = path;
	CreateModel();
}

//==============================================================================
// ���_�V�F�[�_�[���쐬����
//==============================================================================
void IGameObject::CreateVSShader(const wchar_t* vsPath)
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �p�X��ǂݍ���
	std::vector<uint8_t> _vs = DX::ReadData(vsPath);

	// �V�F�[�_�[���쐬
	DX::ThrowIfFailed(
		_device->CreateVertexShader(_vs.data(), _vs.size(), nullptr,m_VS.ReleaseAndGetAddressOf())
	);
}

//==============================================================================
// �s�N�Z���V�F�[�_�[���쐬����
//==============================================================================
void IGameObject::CreatePSShader(const wchar_t* psPath)
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �p�X��ǂݍ���
	std::vector<uint8_t> _ps = DX::ReadData(psPath);

	// �V�F�[�_�[���쐬
	DX::ThrowIfFailed(
		_device->CreatePixelShader(_ps.data(), _ps.size(), nullptr, m_PS.ReleaseAndGetAddressOf())
	);
}

//==============================================================================
// �W�I���g���V�F�[�_�[���쐬����
//==============================================================================
void IGameObject::CreateGSShader(const wchar_t* gsPath)
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �p�X��ǂݍ���
	std::vector<uint8_t> _gs = DX::ReadData(gsPath);

	// �V�F�[�_�[���쐬
	DX::ThrowIfFailed(
		_device->CreateGeometryShader(_gs.data(), _gs.size(), nullptr, m_GS.ReleaseAndGetAddressOf())
	);
}
