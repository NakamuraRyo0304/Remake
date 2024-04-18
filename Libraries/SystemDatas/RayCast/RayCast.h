/*
 *	@File	RayCast.h
 *	@Brief	���C���΂��ăX�N���[�����W�����[���h���W�ɕϊ�����B
 *	@Date	2023-05-26
 *  @Author NakamuraRyo
 */

class RayCast
{
public:

	// ���[���h�ϊ���̃}�E�X���W�̎擾
	const DirectX::SimpleMath::Vector3& GetConvertedPosition() { return m_convertPosition; }

	// �s���ݒ�
	void SetMatrix(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
	{
		m_view = view; m_projection = proj;
	}

	// �R���X�g���N�^
	RayCast();
	// �f�X�g���N�^
	~RayCast();
	// �X�V
	void Update();

private:

	// ���C���΂��Ēn�ʂƂ̌�_�����
	DirectX::SimpleMath::Vector3 ShotRay();
	// �X�N���[�����W�����[���h���W�ɕϊ�����
	DirectX::SimpleMath::Vector3 ConvertScreenToWorld(int mx, int my, float fz, int width, int height,
		DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:

	// �}�E�X�����[���h���W�ɕϊ������l��ۑ�����ϐ�
	DirectX::SimpleMath::Vector3 m_convertPosition;
	// �s��
	DirectX::SimpleMath::Matrix m_view, m_projection;
	// �X�N���[���T�C�Y
	DirectX::SimpleMath::Vector2 m_screenSize;

};