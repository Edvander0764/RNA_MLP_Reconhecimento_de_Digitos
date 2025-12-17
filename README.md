# 🧠 Rede Neural para Reconhecimento de Dígitos (0 e 1) – Matriz 4×4

Este projeto implementa uma **Rede Neural Artificial do tipo Perceptron Multicamadas (MLP)**, desenvolvida em **linguagem C**, com o objetivo de reconhecer os dígitos **0** e **1** representados em uma **matriz 4×4 de pixels binários**.

O código foi desenvolvido com foco **didático**, permitindo acompanhar todas as etapas do **forward**, **cálculo do erro**, **backpropagation** e **atualização dos pesos e bias**.

---

## 📌 Estrutura da Rede Neural

A arquitetura da rede é composta por:

- **16 neurônios de entrada**  
  Representam os pixels de uma imagem 4×4.
- **1 camada oculta com 2 neurônios**
- **1 neurônio de saída**
- **Função de ativação sigmoide**
- **Bias explícito** em todas as camadas

16 Entradas → 2 Neurônios Ocultos → 1 Saída
bias bias bias


---

## 🎯 Objetivo

Classificar uma imagem 4×4 binária como:

- **0 → Dígito 0**
- **1 → Dígito 1**

A saída da rede é um valor contínuo entre 0 e 1.  
Valores **≥ 0.5** são interpretados como **1**, e valores **< 0.5** como **0**.

---

## 🧩 Representação da Imagem (Matriz 4×4)

Cada imagem é transformada em um **vetor de 16 posições**, conforme o mapeamento abaixo:

| 01 | 02 | 03 | 04 |
|---|---|---|---|
| 05 | 06 | 07 | 08 |
| 09 | 10 | 11 | 12 |
| 13 | 14 | 15 | 16 |


Cada posição recebe valor **0 ou 1**, indicando a ausência ou presença de pixel.

---

## 📚 Conjunto de Treinamento

O conjunto de treinamento contém **6 amostras**, sendo:

- **3 exemplos do dígito 0**
- **3 exemplos do dígito 1**

Exemplo do dígito **0**:

| 1 | 1 | 1 | 1 |
|---|---|---|---|
| 1 | 0 | 0 | 1 |
| 1 | 0 | 0 | 1 |
| 1 | 1 | 1 | 1 |


Exemplo do dígito **1**:

| 0 | 1 | 0 | 0 |
|---|---|---|---|
| 1 | 1 | 0 | 0 |
| 0 | 1 | 0 | 0 |
| 1 | 1 | 1 | 0 |


---

## ⚙️ Função de Ativação

A função utilizada é a **sigmoide**:

\[
\sigma(x) = \frac{1}{1 + e^{-x}}
\]

Sua derivada é utilizada no processo de backpropagation:

\[
\sigma'(y) = y(1 - y)
\]

---

## ➕ Implementação do Bias

O **bias foi implementado de forma explícita**, como um termo independente somado à combinação linear dos pesos.

### Camada Oculta
\[
h_i = \sigma\left(\sum w_{ij}x_j + b_{1i}\right)
\]

### Camada de Saída
\[
y = \sigma\left(\sum w_i h_i + b_2\right)
\]

> ⚠️ O bias **não é tratado como uma entrada adicional**, portanto o número de entradas permanece **16**.

---

## 🔁 Treinamento da Rede

O treinamento ocorre por meio do algoritmo **Backpropagation**, seguindo as etapas:

1. **Forward propagation**
2. **Cálculo do erro**
3. **Cálculo dos gradientes**
4. **Atualização dos pesos e bias**

### Parâmetros de Treinamento

| Parâmetro | Valor |
|----------|-------|
| Épocas máximas | 1000 |
| Taxa de aprendizado | 0.1 |
| Função de ativação | Sigmoide |

O treinamento é encerrado antecipadamente caso a rede **classifique corretamente todas as amostras** em uma época.

---

## 🧪 Modo de Teste

Após o treinamento, o programa entra em modo interativo, onde o usuário:

1. Insere os **16 valores (0 ou 1)** da matriz 4×4
2. A rede calcula a saída
3. O dígito reconhecido é exibido

Exemplo de saída:

Saída da rede: 0.982314
Resultado: DIGITO 1


---

## 🛠️ Tecnologias Utilizadas

- Linguagem C
- Biblioteca `math.h`
- Compilação em ambiente Windows

---

## 📎 Observações Finais

Este projeto tem caráter **educacional**, com ênfase na compreensão dos conceitos fundamentais de:

- Redes Neurais Artificiais
- Perceptron Multicamadas
- Backpropagation
- Bias e funções de ativação

O código foi escrito de forma clara e comentada para facilitar o aprendizado.

---

## 👤 Autor

**Edvander Sperber**  
Estudante de Engenharia de Computação  
Instituto Federal Fluminense – IFF


