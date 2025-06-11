#!/bin/bash

echo "=== Test de quotes complexes ==="

echo "Test 1: echo \"Only Simple''\"\"\"\"\'\'\"\""
echo "Expected: Only Simple''\"\"''\""

echo
echo "Test 2: echo \"hello world\""
echo "Expected: hello world"

echo
echo "Test 3: echo 'hello world'"
echo "Expected: hello world"

echo
echo "Test 4: echo \"mix'ed\""
echo "Expected: mix'ed"

echo
echo "Test 5: echo 'mix\"ed'"
echo "Expected: mix\"ed"
