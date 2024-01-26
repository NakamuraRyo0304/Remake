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

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using Json = nlohmann::json;

class JsonHelper
{
private:

	// Json
	Json m_json;

	// �t�@�C���p�X
	std::wstring m_path;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	JsonHelper();
	~JsonHelper();

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <param name="path">�t�@�C���p�X</param>
	/// <returns>��������</returns>
	bool Load(const wchar_t* path);

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="data">Json�f�[�^��ϊ�����������</param>
	/// <returns>�Ȃ�</returns>
	bool Write(std::string str);

	/// <summary>
	/// �f�[�^�̎擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>��͍ς݃f�[�^</returns>
	Json GetData() { return m_json; }

	/// <summary>
	/// �p�X�̐ݒ�(��ɊJ�����f�[�^�𑼂̃t�@�C���ɏ����o�������Ƃ��Ɏg��)
	/// </summary>
	/// <param name="path">�����o���p�X</param>
	/// <returns>�Ȃ�</returns>
	void SetPath(const wchar_t* path) { m_path = path; }
};

#endif // JSONHELPER