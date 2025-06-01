#!/bin/bash

echo "=== Test des améliorations du Minishell ==="
echo ""

echo "1. Test heredoc simple:"
./minishell << 'EOF'
cat << DELIMITER
Hello World
DELIMITER
exit
EOF

echo ""
echo "2. Test heredoc avec variables:"
./minishell << 'EOF'
export TEST_VAR="testing"
cat << EOF2
Variable: $TEST_VAR
User: $USER
EOF2
exit
EOF

echo ""
echo "3. Test interruption avec Ctrl+C (Soyez prêt à appuyer sur Ctrl+C dans le heredoc):"
echo "   Note: Ce test nécessite une interaction manuelle"

echo ""
echo "=== Tests terminés ==="
