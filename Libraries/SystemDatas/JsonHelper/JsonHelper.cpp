/*
 *	@File	JsonHelper.cpp
 *	@Brief	json�t�@�C���̃w���p�[�N���X�B
 *	@Date	2023-01-18
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include <iostream>
#include <fstream>
#include "JsonHelper.h"

// �R���X�g���N�^
JsonHelper::JsonHelper()
	:
	m_json(),
	m_path()
{
}

// �f�X�g���N�^
JsonHelper::~JsonHelper()
{
	m_json.clear();
	m_path.clear();
}

// �ǂݍ���
bool JsonHelper::Load(const wchar_t* path)
{
	// Json�t�@�C���̓ǂݍ���
	std::ifstream ifs(path, std::ios::in);

	if (!ifs) return EXIT_FAILURE;

	// Json�f�[�^�̎��o��
	ifs >> m_json;

	// Json�t�@�C�������
	ifs.close();

	// �p�X��ۑ����Đ���I��
	m_path = path;
	return EXIT_SUCCESS;
}

// �����o��
bool JsonHelper::Write(std::string str)
{
	// Json�t�@�C���̏�������
	std::ofstream ofs(m_path, std::ios::out);

	if (!ofs) return EXIT_FAILURE;

	// Json�f�[�^�̏����o��
	ofs << str;

	// Json�t�@�C�������
	ofs.close();

	return EXIT_SUCCESS;
}
