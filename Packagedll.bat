"C:\Program Files\MRE SDK V3.0.00\tools\DllPackage.exe" "D:\MyGitHub\vsm_cln\vsm_cln.vcproj"
if %errorlevel% == 0 (
 echo postbuild OK.
  copy vsm_cln.vpp ..\..\..\MoDIS_VC9\WIN32FS\DRIVE_E\vsm_cln.vpp /y
exit 0
)else (
echo postbuild error
  echo error code: %errorlevel%
  exit 1
)

