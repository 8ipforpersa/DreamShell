-----------------------------------------
--                                     --
-- @name:     Dial-up connect script   --
-- @author:   SWAT                     --
-- @url:      http://www.dc-swat.ru    --
--                                     --
-----------------------------------------
--

ShowConsole();
print("To get back GUI press: Start, A, Start\n");
if OpenModule(os.getenv("PATH") .. "/modules/ppp.klf") then
    print("Dialing...\n");
    os.execute("ppp -i");
end
Sleep(2000);
HideConsole();
