/*
 *  @File   FlagManager.h
 *  @Brief  ���Ǘ��N���X�B
 *  @Date   2024-02-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FLAGMANAGER
#define FLAGMANAGER

class Flag;
class FlagManager
{
public:

	// �t���O��ǉ�
	void AddFlag(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 dropped, const int& max);
	// �t���O���폜
	void PickFlag();
	// �t���O�z����擾
	std::vector<std::unique_ptr<Flag>>& GetFlags() { return m_flags; }

	// ��Ԑ擪�̃t���O���L�т�������True��Ԃ�
	bool IsFirstArrived();

	// ��Ԑ擪�̃p�X�̍��W���擾
	const DirectX::SimpleMath::Vector3& GetFirstPath();

public:

	// �R���X�g���N�^
	FlagManager();
	// �f�X�g���N�^
	~FlagManager();
	// �X�V
	void Update();
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr);

private:

	// ���̕`��ʒu
	std::vector<std::unique_ptr<Flag>> m_flags;
	// �擪���W
	DirectX::SimpleMath::Vector3 m_firstPosition;

};

#endif // FLAGMANAGER