fltk用x64的編譯器會出問題，請改用x86的。
如果專案設定跑掉，請座以下步驟：
１．Include目錄新增: $(SolutionDir)fltk-1.3.8
２．程式庫目錄新增: $(SolutionDir)fltk-1.3.8\lib
３．連結器->輸入->其他相依性 中，請加入這些全部:
	Comctl32.lib
	fltkd.lib
	fltkpngd.lib
	fltkformsd.lib
	fltkimagesd.lib
	fltkgld.lib
	fltkjpegd.lib
	fltkzlibd.lib