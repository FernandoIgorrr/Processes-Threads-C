#!/bin/bash

# Defina o número de vezes que você deseja executar o binário
n=10

# Use um loop "while" para executar o binário repetidamente
count=0
while [ $count -lt $n ]; do
  # Comando para executar o binário aqui
  ./seq M1 M2

  # Atualize a contagem
  count=$((count + 1))
done
