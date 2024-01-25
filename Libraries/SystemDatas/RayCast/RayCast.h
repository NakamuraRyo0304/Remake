/*
 *	@File	RayCast.h
 *	@Brief	���C���΂��ăX�N���[�����W�����[���h���W�ɕϊ�����B
 *	@Date	2023-05-26
 *  @Author NakamuraRyo
 */

class RayCast
{
private:
	// �}�E�X�����[���h���W�ɕϊ������l��ۑ�����ϐ�
	DirectX::SimpleMath::Vector3 m_convertPosition;

	// �s��
	DirectX::SimpleMath::Matrix m_view, m_projection;

	// �X�N���[���T�C�Y
	DirectX::SimpleMath::Vector2 m_screenSize;

public:
	RayCast();
	~RayCast();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

private:

	/// <summary>
	/// ���C���΂��Ēn�ʂƂ̌�_�����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>���������n�ʂƂ̌�_</returns>
	DirectX::SimpleMath::Vector3 ShotRay();

	/// <summary>
	/// �X�N���[�����W�����[���h���W�ɕϊ�����
	/// </summary>
	/// <param name="mx">�}�E�XX</param>
	/// <param name="my">�}�E�XY</param>
	/// <param name="fz">�C�ӂ̒l</param>
	/// <param name="width">��ʉ���</param>
	/// <param name="height">��ʏc��</param>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <returns>�ϊ���̍��W</returns>
	DirectX::SimpleMath::Vector3 ConvertScreenToWorld(int mx, int my, float fz, int width, int height,
		DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

public:

	/// <summary>
	/// ���[���h�ϊ���̃}�E�X���W�̎擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>���[���h���W�ɂȂ����}�E�X���W</returns>
	const DirectX::SimpleMath::Vector3& GetConvertedPosition() { return m_convertPosition; }

	/// <summary>
	/// �s���ݒ�
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <returns>�Ȃ�</returns>
	void SetMatrix(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
	{ m_view = view; m_projection = proj; }
};