namespace SDX_BSC
{
	using namespace SDX;

	namespace Save
	{
		bool SaveAndLoad(FileMode �ۑ�or�ǂݍ���)
		{
			//�o�C�i���`���ŕۑ�
			File file("file/save/save.dat", �ۑ�or�ǂݍ���, false);

			//�t�@�C���������̂ɓǂݍ������Ƃ����珉���f�[�^�ɂ���
			if (file.GetFileMode() == FileMode::None)
			{
				return false;
			}

			return true;
		}

	}
}

