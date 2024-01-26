/*
 *	@File	IUserInterface.h
 *	@Brief	UI�N���X�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#ifndef IUSERINTERFACE
#define IUSERINTERFACE

//==============================================================================
// ��ʗv�f
//==============================================================================
#include "Libraries/SystemDatas/Button/Button.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class IUserInterface
{
private:

	// ��ʃT�C�Y
	DirectX::SimpleMath::Vector2 m_screenSize;

	// �ő��ʃT�C�Y
	DirectX::SimpleMath::Vector2 m_maxScreenSize;

	// ��ʊg�嗦
	DirectX::SimpleMath::Vector2 m_screenRate;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scS">��ʃT�C�Y</param>
	/// <param name="mscS">�ő�T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	IUserInterface(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~IUserInterface() = default;

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	virtual void Update() = 0;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	virtual void Draw() = 0;

public:

	// ��ʊg�嗦���擾
	const DirectX::SimpleMath::Vector2& GetScreenRate() { return m_screenRate; }
	// ��ʊg�嗦��ݒ�
	void SetScreenRate(const DirectX::SimpleMath::Vector2& rate) { m_screenRate = rate; }

	// ��ʃT�C�Y���擾
	const DirectX::SimpleMath::Vector2& GetScreenSize() { return m_screenSize; }
	// ��ʃT�C�Y��ݒ�
	void SetScreenSize(const DirectX::SimpleMath::Vector2& size) { m_screenSize = size; }

	// �ő��ʃT�C�Y���擾
	const DirectX::SimpleMath::Vector2& GetMaxScreenSize() { return m_maxScreenSize; }
	// �ő��ʃT�C�Y��ݒ�
	void SetMaxScreenSize(const DirectX::SimpleMath::Vector2& size) { m_maxScreenSize = size; }
};

#endif // IUSERINTERFACE