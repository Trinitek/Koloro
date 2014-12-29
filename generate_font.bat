
@rem Generate PXL files from the font character PNG files
@cd font

@for %%x in (png\*.png) do @java -jar ..\monochrome.jar %%x
@move /Y png\*.pxl .

@rem Generate a header file from the compressed PXL files
@md inc 2> nul

@setlocal
@set filelist=
@for %%f in (*.pxl) do @call :concat %%f
bin2c -m -o inc\charset.h %filelist%
@endlocal
@cd ..
@goto :eof

:concat
@set filelist=%filelist% %1
:eof