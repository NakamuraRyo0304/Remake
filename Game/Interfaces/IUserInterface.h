/*
 *	@File	IUserInterface.h
 *	@Brief	UI�N���X�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#ifndef IUSERINTERFACE
#define IUSERINTERFACE

class IUserInterface
{
public:

	// �f�X�g���N�^
	virtual ~IUserInterface() = default;
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;

};

#endif // IUSERINTERFACE