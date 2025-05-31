# 🐻 Minishell - Mininours

Un shell minimal développé en C dans le cadre du cursus 42. Ce projet implémente les fonctionnalités de base d'un shell Unix avec gestion des commandes, redirections, pipes et variables d'environnement.

## 📋 Description

Minishell (surnommé "Mininours") est une implémentation simplifiée d'un shell Unix. Il permet d'exécuter des commandes, de gérer les variables d'environnement, et d'utiliser les fonctionnalités de base d'un terminal interactif.

## ✨ Fonctionnalités

### Commandes intégrées (Built-ins)
- `echo` - Affiche du texte avec option `-n`
- `cd` - Change de répertoire
- `pwd` - Affiche le répertoire courant
- `export` - Définit ou affiche les variables d'environnement
- `unset` - Supprime des variables d'environnement
- `env` - Affiche l'environnement
- `exit` - Quitte le shell

### Fonctionnalités avancées
- **Exécution de commandes** : Programmes externes et chemins absolus/relatifs
- **Variables d'environnement** : Support complet avec expansion `$VAR`
- **Redirections** :
  - `>` : Redirection de sortie
  - `>>` : Redirection en mode append
  - `<` : Redirection d'entrée
  - `<<` : Here document
- **Pipes** : Communication entre processus avec `|`
- **Gestion des guillemets** : Simple `'` et double `"`
- **Gestion des signaux** : `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- **Historique** : Navigation dans l'historique des commandes

## 🛠️ Compilation

### Prérequis
- GCC ou Clang
- Make
- Readline library (`libreadline-dev` sur Ubuntu/Debian)

### Installation
```bash
# Cloner le projet
git clone [URL_DU_REPO]
cd mininours

# Compiler
make

# Lancer le shell
./minishell
```

### Commandes Make disponibles
```bash
make        # Compile le projet
make clean  # Supprime les fichiers objets
make fclean # Supprime tout (objets + exécutable)
make re     # Recompile tout
```

## 🏗️ Architecture

```
mininours/
├── headers/              # Fichiers d'en-tête
│   ├── minishell.h      # Déclarations principales
│   └── structures.h     # Structures de données
├── libft/               # Bibliothèque personnelle
├── libUtils/            # Utilitaires pour les listes
├── src/                 # Code source principal
│   ├── main.c          # Point d'entrée
│   ├── built-in/       # Commandes intégrées
│   ├── exec/           # Système d'exécution
│   ├── parsing/        # Analyseur syntaxique
│   ├── signals/        # Gestion des signaux
│   └── utils/          # Fonctions utilitaires
└── Makefile            # Script de compilation
```

## 🚀 Utilisation

### Exemples de commandes
```bash
# Commandes simples
ls -la
echo "Hello World"
cd /tmp

# Variables d'environnement
export MY_VAR="test"
echo $MY_VAR
unset MY_VAR

# Redirections
ls > output.txt
cat < input.txt
echo "line" >> file.txt

# Pipes
ls | grep .c
cat file.txt | wc -l

# Here document
cat << EOF
Ceci est un
here document
EOF
```

### Gestion des guillemets
```bash
echo 'Simple quotes: $USER'     # Affiche littéralement $USER
echo "Double quotes: $USER"     # Expand la variable $USER
```

## 🔧 Debugging

Le projet inclut un fichier de suppression Valgrind pour le debugging :
```bash
valgrind --leak-check=full --suppressions=suppression.supp ./minishell
```

## 📝 Notes techniques

- **Parsing** : Utilise un tokenizer pour analyser les commandes
- **Exécution** : Fork/exec pour les processus enfants
- **Mémoire** : Gestion rigoureuse avec fonctions de libération
- **Signaux** : Handlers personnalisés pour les interruptions
- **Readline** : Interface utilisateur avec historique et édition

## 🎯 Objectifs pédagogiques

Ce projet permet d'apprendre :
- La programmation système en C
- La gestion des processus et des signaux
- Le parsing et l'analyse syntaxique
- La gestion de la mémoire
- L'architecture logicielle modulaire

## 👥 Auteurs

- **abosc** - Développeur principal

## 📄 Licence

Ce projet est développé dans le cadre du cursus 42. Voir les règles de l'école pour l'utilisation du code.

---

*"Un shell minimal mais fonctionnel - Mininours rugit doucement mais efficacement !"* 🐻
