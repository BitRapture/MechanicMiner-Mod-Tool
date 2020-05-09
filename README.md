# MechanicMiner-Mod-Tool
A mod tool for the game, Mechanic Miner.

This tool allows for asset dumping and asset repacking.

WARNING: Repacking works however the assets must be identical in size for changes to be occurred, even then it is not guaranteed that they will show up in-game. I am pretty sure that in order to make texture packs I need to find out what the other asset file does.

## TO-DO
* Unlock the secrets that `main.mechanicminer_asset_64_links` holds for texture packs
  * Customise UI layout once it's been figured out
    * Implement extra features for better UX when creating texture packs
  * Create texture pack file (`texture_pack_example.mmmtp`)
    * Create special file header to lessen the likelihood of app breaking
* Add more asset options
  * Dump WAVE files
    * Repack WAVE files (will just be included within the repacking option)
  * Dump sprite sheets
    * John sprite sheets
    * Jones sprite sheets
    * Mob sprite sheets
  * Dump grouped sprite sheets
    * MM font sheets
    * Block sheets
