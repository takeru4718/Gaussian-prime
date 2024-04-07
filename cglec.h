/*******************************************************
    コンピュータグラフィックス学習用ライブラリ
	cglec   Rel 1.2

    関西大学システム理工学部電気電子情報工学科
	科目：コンピュータグラフィックス
	担当：松島恭治
	All right reserved by 松島恭治

	2020/05/27 カラー画像描画関数の追加
	2018/04/11 SaveAsGrayBmp()でガンマ値を2.2に変更
	2018/05/11 CglPaintTriangleのバグフィックス
	*******************************************************/

#ifndef __APPLE__

///////// 以下はWindows用DLLのための定義
#ifdef CGLEC_EXPORTS
#define CGLEC_API __declspec(dllexport)
#else
#define CGLEC_API __declspec(dllimport)
#endif

// cgrec.libのリンクを指定
#if !defined(CGLEC_EXPORTS)
#	pragma comment (lib, "cglec.lib")
#endif

///////// マックの場合
#else

#define CGLEC_API 

#endif

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

///////// Image型の構造体の定義
struct Image
{
	unsigned char* Data;	// イメージデータ本体へのポインタ
	int	Nx;					// 横方向ピクセル数
	int Ny;					// 縦方向ピクセル数
};


///////// ColorImage型の構造体の定義
struct ColorImage
{
	unsigned char* DataR;	// 赤プレーンデータ本体へのポインタ
	unsigned char* DataG;	// 緑プレーンデータ本体へのポインタ
	unsigned char* DataB;	// 青プレーンデータ本体へのポインタ
	int	Nx;					// 横方向ピクセル数
	int Ny;					// 縦方向ピクセル数
};

///////// Point型の構造体の定義
struct Point
{
	int x;
	int y;
};

///////// ここからが関数のプロトタイプ宣言

// 画像構造体imgの画像の全ピクセルをvalで塗りつぶす
CGLEC_API void CglSetAll(Image img, unsigned char val);

// ファイル名fnameで，画像構造体imgのグレイスケール画像をbmp形式ファイルとして保存する
CGLEC_API void CglSaveGrayBMP(Image img, const char* fname);

// ファイル名fnameで，画像構造体red，blue，greenのカラー画像をbmp形式ファイルとして保存する
CGLEC_API void CglSaveColorBMP(Image red, Image green, Image blue, const char* fname);

// (x1, y1) - (x2, y2)の範囲でグレイレベルlevelの四角形を塗りつぶす
CGLEC_API void CglPaintRect(Image img, int x1, int y1, int x2, int y2, int level);

// (x0, y0)を中心とした半径rの円をグレイレベルlevelで塗りつぶす
CGLEC_API void CglPaintCircle(Image img, int x0, int y0, int r, int level);

// 3点(x1, y1), (x2, y2), (x3, y3)からなる三角形をグレイレベルlevelを塗りつぶす
CGLEC_API void CglPaintTriangle(Image img, int x1, int y1, int x2, int y2, int x3, int y3, int level);

// 2点(x1, y1), (x2, y2)の間にグレイレベルgの線分を描く
CGLEC_API void CglDrawLine(Image img, int x1, int y1, int x2, int y2, int g);

// 画像構造体imgの画像に点列points[]で示される画像を描く
CGLEC_API void CglDrawLines(Image img, Point points[], int n, int g);

///////////////////////////////////////////////////////////////////////////////////////

//ピクセル数 nx × ny のカラー画像用メモリを確保してColorImage構造体を作成する
CGLEC_API ColorImage CglInitColorImage(int nx, int ny);

//カラー画像imgの全ピクセルにカラー(R, G, B)をセットする
CGLEC_API void CglColorSetAll(ColorImage img, int R, int G, int B);

//カラー画像imgをファイル名fnameで保存する
CGLEC_API void CglSaveColorImage(ColorImage img, const char* fname);

//カラー画像imgのメモリを開放する
CGLEC_API void CglFreeColorImage(ColorImage img);

//カラー画像imgのピクセル(x, y)にカラー(R, G, B)を設定する．パラメータチェックはない
CGLEC_API void CglSetPixel(ColorImage img, int x, int y, int R, int G, int B);

//カラー画像imgのピクセル(x, y)にカラー(R, G, B)を安全に設定する
CGLEC_API void CglSetSafePixel(ColorImage img, int x, int y, int R, int G, int B);

//カラー画像imgに2点(x1, y1), (x2, y2)を対角とする四角形をカラー(R, G, B)で塗りつぶす
CGLEC_API void CglPaintColorRect(ColorImage img, int x1, int y1, int x2, int y2, int R, int G, int B);

//カラー画像imgに，2点(x1, y1), (x2, y2)の間にカラー(R, G, B)の線分を描く
CGLEC_API void CglDrawColorLine(ColorImage img, int x1, int y1, int x2, int y2, int R, int G, int B);

//カラー画像imgに，中心(x0, y0)で，内径r1, 外径r2，内側カラー(R1, G1, B1)，外側カラー(R2, G2, B2)のグラデーションがあるリングを描画する
CGLEC_API void CglPaintGradationRing(ColorImage img, int x0, int y0, int r1, int r2, int R1, int G1, int B1, int R2, int G2, int B2);

// (x0, y0)を中心とした半径rの円をカラー(R, G, B)で塗りつぶす
CGLEC_API void CglPaintColorCircle(ColorImage img, int x0, int y0, int r, int R, int G, int B);

// 3点(x1, y1), (x2, y2), (x3, y3)からなる三角形をカラー(R, G, B)で塗りつぶす
CGLEC_API void CglPaintColorTriangle(ColorImage img, int x1, int y1, int x2, int y2, int x3, int y3, int R, int G, int B);

///////////////////////////////////////////////////////////////////////////////////////
