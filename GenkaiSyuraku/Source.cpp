//#define GENKAI_SYURAKU_TOUCH

constexpr int frame_size{ 1 };
constexpr int title_frame_x{ 650 / frame_size };
constexpr int title_frame_y{ 800 / frame_size };
constexpr int button1_frame_x{ 1408 / frame_size };
constexpr int button1_frame_y{ 568 / frame_size };
constexpr int button2_frame_y{ 568 / frame_size };
#include "MainFrame.hpp"

#ifdef __ANDROID__
int android_main(void) {
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif

	// ログ出力を行わない
	::DxLib::SetOutApplicationLogValidFlag(FALSE);

	// UTF-8に変更
	::DxLib::SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

	// ウインドウモードにする
#ifndef __ANDROID__
	::DxLib::ChangeWindowMode(TRUE);
	::DxLib::SetWindowIconID(22);
	::DxLib::SetWindowSizeChangeEnableFlag(TRUE);
	::DxLib::SetAlwaysRunFlag(TRUE);
#endif

	// 画面の解像度を指定する
	::DxLib::SetGraphMode(1920 / frame_size, 1080 / frame_size, 32);

	// ウインドウのタイトルを変更する
#ifndef __ANDROID__
	::DxLib::SetMainWindowText(u8"GenkaiSyuraku");
	::DxLib::SetDXArchiveExtension("as");
#endif

	// ライブラリの初期化
	if (::DxLib::DxLib_Init() == -1) return false;

	// ロード中表示
	const int load_font{ ::DxLib::CreateFontToHandle(nullptr, 100 / frame_size, 0, DX_FONTTYPE_NORMAL) };

	::DxLib::DrawStringToHandle(title_frame_x, title_frame_y, u8"Now Loading...\n■□□□□", 0xffffffff, load_font);
	::DxLib::LoadGraphScreen(0, 0, u8"image/title1.png", FALSE);

	::DxLib::DrawStringToHandle(title_frame_x, title_frame_y, u8"Now Loading...\n■■□□□", 0xffffffff, load_font);
	::DxLib::ProcessMessage();

	// メインフレームを定義
	::MainFrame mainFrame;
	::DxLib::DrawStringToHandle(title_frame_x, title_frame_y, u8"\n■■■□□", 0xffffffff, load_font);
	::DxLib::ProcessMessage();

	//ゲームを初期化
	mainFrame.init(load_font);

	// ゲームループ
	while (mainFrame.loop());

	// ゲームの終了処理
	mainFrame.end();

	return 0;
}