/*
 *	@File	IUserInterface.h
 *	@Brief	UI�N���X�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#ifndef IUSERINTERFACE
#define IUSERINTERFACE

#include "Libraries/SystemDatas/Button/Button.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class IUserInterface
{
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

	// �R���X�g���N�^
	IUserInterface(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// �f�X�g���N�^
	~IUserInterface() = default;
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;

private:

	// ��ʃT�C�Y
	DirectX::SimpleMath::Vector2 m_screenSize;

	// �ő��ʃT�C�Y
	DirectX::SimpleMath::Vector2 m_maxScreenSize;

	// ��ʊg�嗦
	DirectX::SimpleMath::Vector2 m_screenRate;

};

#endif // IUSERINTERFACE