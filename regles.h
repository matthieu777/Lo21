typedef struct proposition {
       char* texte;
       struct proposition *next;
}Proposition;

typedef Proposition* Premisse;
typedef char* Conclusion;

typedef struct Regle {
       Premisse premisse;
       Conclusion conclusion;
}regle;
