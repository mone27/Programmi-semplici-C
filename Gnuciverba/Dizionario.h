
//===============================================================================================
//Questo dizionario comprende parole riguardanti l'informatica, la privacy e il sistema GNU/Linux
//===============================================================================================


//matrice di stringhe, meno personalizzabile di un vettore di vettori di stringhe ma molto piu' comoda da dichiarare
//per far riferimento a PRIVACY occorre chiamare dizionario[4][6] senza alcun operatore di risoluzione.
#ifdef LINUX
 
  #define NPAROLE 15  //Numero di parole per ogni lunghezza
  #define LPAROLE 7   //Nuero di lunghezze di parole

  char *dizionario[LPAROLE][NPAROLE]={
    {"GNU","TUX","LUG","MIT","GCC","GPG","APT","NSA","GIT","FSF","EFF","USB","NOX","UNI","TOR"},          
    {"ARCH","RUST","JAVA","HTML","SUDO","ROOT","SNAP","KALI","LEAK","WINE","INIT","UDOO","SENX","EINK","BASH"},   
    {"LINUS","LINUX","UNIX","PRISM","APPLE","TERES","INODE","NIXON","PUPPY","EMACS","INTEL","GNOME","ORFOX","UNITY","REDOX"}, 
    {"DISTRO","FEDORA","DEBIAN","KERNEL","PACMAN","GITHUB","OLIMEX","GENTOO","VULCAN","EDWARD","UBUNTU","BASHRC","SCRIPT","REDHAT","APACHE"},
    {"RICHARD","MRROBOT","PULPINO","ARDUINO","ASSANGE","WINDOWS","SNOWDEN","ANDROID","SAMSUNG","TEMPORA","IPHONEX","PRIVACY","KUBUNTU","XUBUNTU","LINEAGE"}, 
    {"HARDWARE","SOFTWARE","TORVALDS","PARABOLA","STALLMAN","GUARDIAN","SLAKWARE","DEBUGGER","ARPSPOOF","SPOOFING","SNIFFARE","AAAAAAAA","BBBBBBBB","CCCCCCCC","DDDDDDDD"},
    {"RASPBERRY","BACKTRACK","WIKILEAKS","CANONICAL","GNEWSENSE","ARCHLINUX","GNUICECAT","ICEWEASEL","REPLICANT","GNUSCREEN","PACCHETTO","AAAAAAAAA","BBBBBBBBB","CCCCCCCCC","DDDDDDDDD"}
  };
#endif 
