/*
 *	@File	JsonHelper.h
 *	@Brief	json�t�@�C���̃w���p�[�N���X�B
 *	@Date	2023-01-18
 *  @Author NakamuraRyo
 */

// json���C�u�����̃C���N���[�h
#include "json.hpp"
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
////   Json for Modern C++                                   ////
////   Version 3.11.2                                        ////
////   Author Niels Lohmann                                  ////
////   DownLoad for URL : https://github.com/nlohmann/json   ////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

#pragma once
#ifndef JSONHELPER
#define JSONHELPER

// �G�C���A�X�錾
using Json = nlohmann::json;

class JsonHelper
{
public:

	// �f�[�^�̎擾
	Json GetData() const { return m_json; }
	// �p�X�̐ݒ�(��ɊJ�����f�[�^�𑼂̃t�@�C���ɏ����o�������Ƃ��Ɏg��)
	void SetPath(const wchar_t* path) { m_path = path; }

	// �R���X�g���N�^
	JsonHelper();
	// �f�X�g���N�^
	~JsonHelper();
	// �ǂݍ���
	bool Load(const wchar_t* path);
	// ��������
	bool Write(std::string str);

private:

	// Json
	Json m_json;
	// �t�@�C���p�X
	std::wstring m_path;

};

#endif // JSONHELPER