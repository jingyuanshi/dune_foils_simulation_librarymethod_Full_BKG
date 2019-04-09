# dune_foils_simulation_librarymethod_Full_BKG
This is an extension of previous photon code with consideration of radiological backgrounds
Jingyuan Shi @ University of Manchester

1. To generate certain background events(i.g. Rn222), make a soft link:
'ln -s libraryanalyze_light_histo_Rn222.h libraryanalyze_light_histo.h'

2. 'source setupROOT.sh' to set up the environment.

3. 'make -B' to compile

4. './libraryanalyze_light_histo' to generates event.

PS:To modify the position, energy and number of events, one need to edit coresponding .h file (i.g. libraryanalyze_light_histo_Rn222.h)
