@echo off
SetLocal EnableDelayedExpansion
(set PATH=G:\Software\Qt\6.0.1\msvc2019_64\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=G:\Software\Qt\6.0.1\msvc2019_64\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=G:\Software\Qt\6.0.1\msvc2019_64\plugins
)
%*
EndLocal
