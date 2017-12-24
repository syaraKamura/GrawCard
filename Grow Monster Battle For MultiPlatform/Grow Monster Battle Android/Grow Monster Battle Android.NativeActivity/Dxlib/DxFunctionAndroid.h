// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android��p�֐��v���g�^�C�v�錾�p�w�b�_�t�@�C��
// 
// 				Ver 3.19 
// 
// -------------------------------------------------------------------------------

#ifndef __DXFUNCTIONANDROID
#define __DXFUNCTIONANDROID

// �C���N���[�h ------------------------------------------------------------------
#include <android/native_activity.h>
#include <android/window.h>

// ��`---------------------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �\�t�g�̃f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetInternalDataPath( TCHAR *PathBuffer, int PathBufferBytes ) ;

// �\�t�g�̊O���f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetExternalDataPath( TCHAR *PathBuffer, int PathBufferBytes ) ;

// �[���ɐݒ肳��Ă��錾����擾����( �߂�l�@-1�F�G���[�@0�ȏ�F���ꖼ������̊i�[�ɕK�v�ȃo�C�g�� )
extern int GetLanguage( TCHAR *StringBuffer, int StringBufferSize ) ;

// �[���ɐݒ肳��Ă��鍑���擾����( �߂�l�@-1�F�G���[�@0�ȏ�F����������̊i�[�ɕK�v�ȃo�C�g�� )
extern int GetCountry( TCHAR *StringBuffer, int StringBufferSize ) ;

// �A�v���Ŏg�p���Ă��� NativeActivity ���擾����
extern const ANativeActivity *GetNativeActivity( void ) ;

// �f�B�X�v���C�̉𑜓x���擾����
extern int GetAndroidDisplayResolution( int *SizeX, int *SizeY ) ;

// �����x�Z���T�[�̃x�N�g���l���擾����
extern VECTOR GetAccelerometerVector( void ) ;

// �Z���T�[���瓾������p���擾����
// �c����( �n�ʂɑ΂��Ē[���𐂒��Ɏ�������� )�̏ꍇ�ɐ������l���擾�ł��܂�
// �߂�l�� x:���p( �P�ʁF���W�A��  0.0f:�k  ��/2.0f:��  -��/2.0f:��  -�� or ��:�� )
// �߂�l�� y:�O��̌X��( �P�ʁF���W�A��  0.0f:�[�����c�����Ő����̏��  ��/2.0f:�O��������90�x�|�������( ��ʂ���������Ă����� )  -��/2.0f:���������90�x�|�������( ��ʂ��n�ʂ������Ă����� )  -�� or ��:�[�����㉺�������܂Ő����̏�� )
// �߂�l�� z:���E�̌X��( �P�ʁF���W�A��  0.0f:�[�����c�����Ő����̏��  ��/2.0f:�E������90�x�|�������  -��/2.0f:��������90�x�|�������  -�� or ��:�[�����㉺�������܂Ő����̏�� )
extern VECTOR GetOrientationVector( void ) ;

// �Z���T�[�̃x�N�g���l���擾����
extern VECTOR GetAndroidSensorVector( int SensorType /* DX_ANDROID_SENSOR_ACCELEROMETER �Ȃ� */ ) ;

// �j����T�Ɋւ�������擾����
// DayOfWeek : �j��( 1:���j�� 2:���j�� 3:�Ηj�� 4:���j�� 5:�ؗj�� 6:���j�� 7:�y�j�� )
// WeekOfMonth : �����������̉��T�ڂȂ̂��̒l( 1:�P�T��  2:�Q�T��  3:�R�T��  4:�S�T��  5:�T�T�� )
// DayOfWeekInMonth : �����̗j������������ڂɓ����邩�A�̒l( 1:�P���  2:�Q���  3:�R���  4:�S��� ... )
extern int GetAndroidWeekInfo( int *DayOfWeek, int *WeekOfMonth, int *DayOfWeekInMonth ) ;

// �ʒm�𔭍s����
// Title         : �^�C�g��
// SubTitle      : �T�u�^�C�g��
// Icon          : �A�C�R�� ( -1 �Ńf�t�H���g�̃A�C�R�� )
// ShowWhen      : �ʒm������\�����邩 ( TRUE : �\������  FALSE : �\�����Ȃ� )
// AutoCancel    : �ʒm���^�b�v���ꂽ��ʒm���폜���邩 ( TRUE : �^�b�v���ꂽ��ʒm���폜����   FALSE : Cancel �����܂Œʒm���폜���Ȃ� )
// NotifyID      : �ʒmID
// Vibrate       : �U���p�^�[���p�� int�^�z��( ���Ԃ̒P�ʂ̓~���b )�ANULL �̏ꍇ�͐U���Ȃ�( Vibrate[0]:�U����~����  Vibrate[1]:�U������  Vibrate[2]:�U����~����  Vibrate[3]:�U������  ... �ȉ��J��Ԃ� )
// VibrateLength : Vibrate �z��̗v�f��
// LightColor    : �ʒm���̃��C�g�̐F( GetColor �Ŏ擾 )�ALightOnTime �� LightOffTime �� 0 �̏ꍇ�̓��C�g�̓_������
// LightOnTime   : ���C�g�̓_������( �P�ʁF�~���b )
// LightOffTime  : ���C�g�̏�������( �P�ʁF�~���b )
extern int AndroidNotification(
	const TCHAR *Title, const TCHAR *SubTitle, int Icon = -1, int ShowWhen = TRUE,
	int AutoCancel = TRUE, int NotifyId = 0, int *Vibrate = NULL, int VibrateLength = 0,
	unsigned int LightColor = 0, int LightOnTime = 0, int LightOffTime = 0 ) ;

// �ʒm���L�����Z������
// NotifyID : �ʒmID
extern int AndroidNotificationCancel( int NotifyId ) ;

// �S�Ă̒ʒm���L�����Z������
extern int AndroidNotificationCancelAll( void ) ;

// �w��� URL ���u���E�U�ŊJ��( BrowserAppPackageName �� BrowserAppClassName �� NULL �̏ꍇ�͕W���u���E�U�ŊJ�� )
// URL                   : �J��URL
// BrowserAppPackageName : �u���E�U�̃p�b�P�[�W��( NULL �ŕW���u���E�U )
// BrowserAppClassName   : �u���E�U�̃N���X��( NULL �ŕW���u���E�U )
extern int AndroidJumpURL( const TCHAR *URL, const TCHAR *BrowserAppPackageName = NULL, const TCHAR *BrowserAppClassName = NULL ) ;

// �A�v������A�N�e�B�u�ɂȂ����ۂɌĂ΂��R�[���o�b�N�֐���o�^����
extern int SetAndroidLostFocusCallbackFunction( void (* Callback )( void *Data ), void *CallbackData ) ;

// �A�v�����A�N�e�B�u�ɂȂ����ۂɌĂ΂��R�[���o�b�N�֐���o�^����
extern int SetAndroidGainedFocusCallbackFunction( void (* Callback )( void *Data ), void *CallbackData ) ;

// OpenGL �֌W�̏����擾����
extern int GetOpenGLInfo(
	TCHAR **Version = NULL,
	TCHAR **Renderer = NULL,
	TCHAR **Vendor = NULL,
	TCHAR ***ExtensionNames = NULL,
	TCHAR **Shader_Language_Version = NULL,
	int *Shader_Max_Vertex_Attribs = NULL,						// GL_MAX_VERTEX_ATTRIBS
	int *Shader_Max_Vertex_Uniform_Vectors = NULL,				// GL_MAX_VERTEX_UNIFORM_VECTORS
	int *Shader_Max_Varying_Vectors = NULL,						// GL_MAX_VARYING_VECTORS
	int *Shader_Max_Combined_Texture_Image_Units = NULL,		// GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
	int *Shader_Max_Vertex_Texture_Image_Units = NULL,			// GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
	int *Shader_Max_Texture_Image_Units = NULL,					// GL_MAX_TEXTURE_IMAGE_UNITS
	int *Shader_Max_Fragment_Uniform_Vectors = NULL				// GL_MAX_FRAGMENT_UNIFORM_VECTORS
) ;


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // __DXFUNCTIONANDROID

