cd ai_help
sh keygen.sh
ls 
cd key 
ls
rm file*
paste -d '\0' part*.key > main.key
mv main.key ..
cd ..
sh unifier.sh
