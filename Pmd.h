#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>

namespace pmd
{
	/// ヘッダ
	class PmdHeader
	{
	public:
		/// モデル名
		std::string name;
		/// モデル名(英語)
		std::string name_english;
		/// コメント
		std::string comment;
		/// コメント(英語)
		std::string comment_english;

		bool Read(std::ifstream* stream);

		bool ReadExtension(std::ifstream* stream);
	};

	/// 頂点
	class PmdVertex
	{
	public:
		/// 位置
		float position[3];

		/// 法線
		float normal[3];

		/// UV座標
		float uv[2];

		/// 関連ボーンインデックス
		uint16_t bone_index[2];

		/// ボーンウェイト
		uint8_t bone_weight;

		/// エッジ不可視
		bool edge_invisible;

		bool Read(std::ifstream* stream);
	};

	/// 材質
	class PmdMaterial
	{
	public:
		/// 減衰色
		float diffuse[4];
		/// 光沢度
		float power;
		/// 光沢色
		float specular[3];
		/// 環境色
		float ambient[3];
		/// トーンインデックス
		uint8_t toon_index;
		/// エッジ
		uint8_t edge_flag;
		/// インデックス数
		uint32_t index_count;
		/// テクスチャファイル名
		std::string texture_filename;
		/// スフィアファイル名
		std::string sphere_filename;

		bool Read(std::ifstream* stream);
	};

	enum class BoneType : uint8_t
	{
		Rotation,
		RotationAndMove,
		IkEffector,
		Unknown,
		IkEffectable,
		RotationEffectable,
		IkTarget,
		Invisible,
		Twist,
		RotationMovement
	};

	/// ボーン
	class PmdBone
	{
	public:
		/// ボーン名
		std::string name;
		/// ボーン名(英語)
		std::string name_english;
		/// 親ボーン番号
		uint16_t parent_bone_index;
		/// 末端ボーン番号
		uint16_t tail_pos_bone_index;
		/// ボーン種類
		BoneType bone_type;
		/// IKボーン番号
		uint16_t ik_parent_bone_index;
		/// ボーンのヘッドの位置
		float bone_head_pos[3];

		void Read(std::istream *stream);

		void ReadExpantion(std::istream *stream);
	};

	/// IK
	class PmdIk
	{
	public:
		/// IKボーン番号
		uint16_t ik_bone_index;
		/// IKターゲットボーン番号
		uint16_t target_bone_index;
		/// 再帰回数
		uint16_t interations;
		/// 角度制限
		float angle_limit;
		/// 影響下ボーン番号
		std::vector<uint16_t> ik_child_bone_index;

		void Read(std::istream *stream);
	};

	class PmdFaceVertex
	{
	public:
		int vertex_index;
		float position[3];

		void Read(std::istream *stream);
	};

	enum class FaceCategory : uint8_t
	{
		Base,
		Eyebrow,
		Eye,
		Mouth,
		Other
	};

	class PmdFace
	{
	public:
		std::string name;
		FaceCategory type;
		std::vector<PmdFaceVertex> vertices;
		std::string name_english;

		void Read(std::istream *stream);

		void ReadExpantion(std::istream *stream);
	};

	/// ボーン枠用の枠名
	class PmdBoneDispName
	{
	public:
		std::string bone_disp_name;
		std::string bone_disp_name_english;

		void Read(std::istream *stream);

		void ReadExpantion(std::istream *stream);
	};

	class PmdBoneDisp
	{
	public:
		uint16_t bone_index;
		uint8_t bone_disp_index;

		void Read(std::istream *stream);
	};

	/// 衝突形状
	enum class RigidBodyShape : uint8_t
	{
		/// 球
		Sphere = 0,
		/// 直方体
		Box = 1,
		/// カプセル
		Cpusel = 2
	};

	/// 剛体タイプ
	enum class RigidBodyType : uint8_t
	{
		/// ボーン追従
		BoneConnected = 0,
		/// 物理演算
		Physics = 1,
		/// 物理演算(Bone位置合せ)
		ConnectedPhysics = 2
	};

	/// 剛体
	class PmdRigidBody
	{
	public:
		/// 名前
		std::string name;
		/// 関連ボーン番号
		uint16_t related_bone_index;
		/// グループ番号
		uint8_t group_index;
		/// マスク
		uint16_t mask;
		/// 形状
		RigidBodyShape shape;
		/// 大きさ
		float size[3];
		/// 位置
		float position[3];
		/// 回転
		float orientation[3];
		/// 質量
		float weight;
		/// 移動ダンピング
		float linear_damping;
		/// 回転ダンピング
		float anglar_damping;
		/// 反発係数
		float restitution;
		/// 摩擦係数
		float friction;
		/// 演算方法
		RigidBodyType rigid_type;

		void Read(std::istream *stream);
	};

	/// 剛体の拘束
	class PmdConstraint
	{
	public:
		/// 名前
		std::string name;
		/// 剛体Aのインデックス
		uint32_t rigid_body_index_a;
		/// 剛体Bのインデックス
		uint32_t rigid_body_index_b;
		/// 位置
		float position[3];
		/// 回転
		float orientation[3];
		/// 最小移動制限
		float linear_lower_limit[3];
		/// 最大移動制限
		float linear_upper_limit[3];
		/// 最小回転制限
		float angular_lower_limit[3];
		/// 最大回転制限
		float angular_upper_limit[3];
		/// 移動に対する復元力
		float linear_stiffness[3];
		/// 回転に対する復元力
		float angular_stiffness[3];

		void Read(std::istream *stream);
	};

	/// PMDモデル
	class PmdModel
	{
	public:
		float version;
		PmdHeader header;
		std::vector<PmdVertex> vertices;
		std::vector<uint16_t> indices;
		std::vector<PmdMaterial> materials;
		std::vector<PmdBone> bones;
		std::vector<PmdIk> iks;
		std::vector<PmdFace> faces;
		std::vector<uint16_t> faces_indices;
		std::vector<PmdBoneDispName> bone_disp_name;
		std::vector<PmdBoneDisp> bone_disp;
		std::vector<std::string> toon_filenames;
		std::vector<PmdRigidBody> rigid_bodies;
		std::vector<PmdConstraint> constraints;

		static std::unique_ptr<PmdModel> LoadFromFile(const char *filename);

		/// ファイルからPmdModelを生成する
		static std::unique_ptr<PmdModel> LoadFromStream(std::ifstream *stream);

		static std::wstring FromUTF8(const char* str)
		{
			const unsigned char* s = reinterpret_cast<const unsigned char*>(str);

			static const wchar_t badchar = '?';

			std::wstring ret;

			unsigned i = 0;
			while(s[i])
			{
				try
				{
					if(s[i] < 0x80)         // 00-7F: 1 byte codepoint
					{
						ret += s[i];
						++i;
					}
					else if(s[i] < 0xC0)    // 80-BF: invalid for midstream
						throw 0;
					else if(s[i] < 0xE0)    // C0-DF: 2 byte codepoint
					{
						if((s[i+1] & 0xC0) != 0x80)		throw 1;

						ret +=  ((s[i  ] & 0x1F) << 6) |
								((s[i+1] & 0x3F));
						i += 2;
					}
					else if(s[i] < 0xF0)    // E0-EF: 3 byte codepoint
					{
						if((s[i+1] & 0xC0) != 0x80)		throw 1;
						if((s[i+2] & 0xC0) != 0x80)		throw 2;

						wchar_t ch = 
								((s[i  ] & 0x0F) << 12) |
								((s[i+1] & 0x3F) <<  6) |
								((s[i+2] & 0x3F));
						i += 3;

						// make sure it isn't a surrogate pair
						if((ch & 0xF800) == 0xD800)
							ch = badchar;

						ret += ch;
					}
					else if(s[i] < 0xF8)    // F0-F7: 4 byte codepoint
					{
						if((s[i+1] & 0xC0) != 0x80)		throw 1;
						if((s[i+2] & 0xC0) != 0x80)		throw 2;
						if((s[i+3] & 0xC0) != 0x80)		throw 3;

						unsigned long ch = 
								((s[i  ] & 0x07) << 18) |
								((s[i+1] & 0x3F) << 12) |
								((s[i+2] & 0x3F) <<  6) |
								((s[i+3] & 0x3F));
						i += 4;

						// make sure it isn't a surrogate pair
						if((ch & 0xFFF800) == 0xD800)
							ch = badchar;

						if(ch < 0x10000)	// overlong encoding -- but technically possible
							ret += static_cast<wchar_t>(ch);
						else if(std::numeric_limits<wchar_t>::max() < 0x110000)
						{
							// wchar_t is too small for 4 byte code point
							//  encode as UTF-16 surrogate pair

							ch -= 0x10000;
							ret += static_cast<wchar_t>( (ch >> 10   ) | 0xD800 );
							ret += static_cast<wchar_t>( (ch & 0x03FF) | 0xDC00 );
						}
						else
							ret += static_cast<wchar_t>(ch);
					}
					else                    // F8-FF: invalid
						throw 0;
				}
				catch(int skip)
				{
					if(!skip)
					{
						do
						{
							++i;
						}while((s[i] & 0xC0) == 0x80);
					}
					else
						i += skip;
				}
			}

			return ret;
		}

	};
}