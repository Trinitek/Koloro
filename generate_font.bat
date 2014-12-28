
@rem Generate compressed binaries from the font character PNG files
@cd font
@for %%x in (png\*.png) do @java -jar ..\monochrome.jar %%x
@move /Y png\*.pxl .
@cd ..