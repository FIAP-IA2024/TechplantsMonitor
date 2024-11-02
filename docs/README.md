# FIAP - Faculdade de Informática e Administração Paulista

<p align="center">
<a href= "https://www.fiap.com.br/"><img src="assets/logo-fiap.png" alt="FIAP - Faculdade de Informática e Admnistração Paulista" border="0" width=40% height=40%></a>
</p>

<br>

# TechplantsMonitor

## 👨‍🎓 Integrantes: 
- <a href="https://www.linkedin.com/in/edimilson-ribeiro/">Edimilson Ribeiro</a>
- <a href="https://www.linkedin.com/in/ribeirogab/">Gabriel Ribeiro</a>
- <a href="https://www.linkedin.com/in/jonas-felipe-dos-santos-lima-b2346811b/">Jonas Felipe dos Santos Lima</a>
- <a href="https://www.linkedin.com/in/jacorrea/">Jose Antonio Correa Junior</a>
- <a href="https://www.linkedin.com/in/mstrazzini/">Marcos Trazzini</a>

## 👩‍🏫 Professores:
### Tutor(a) 
- <a href="https://www.linkedin.com/in/lucas-gomes-moreira-15a8452a/">Lucas Gomes Moreira</a>
### Coordenador(a)
- <a href="https://www.linkedin.com/in/profandregodoi/">André Godoi</a>


## 📜 Descrição

 TechplantsMonitor - Sistema de Monitoramento de Lavoura - README

O objetivo educacional deste projeto é criar um sistema inteligente de monitoramento agrícola usando o microcontrolador ESP32 e quatro sensores diferentes. O sistema será capaz de coletar dados do ambiente e tomar decisões automatizadas para otimizar o uso de recursos na agricultura, como a irrigação e o controle de condições climáticas.

 Estrutura do Aplicativo

O sistema é dividido em diversos "módulos" que desempenham funções específicas:

 Funcionalidades do Aplicativo/Solução

 1. Sensor PIR

- Leitura do valor do sensor PIR, se movimento for detectado (pirValue == HIGH).
- Output: uma mensagem é exibida no Serial Monitor: "Movimento detectado! Alarme acionado!".


 2. Sensor DHT 22

- Leitura da umidade com dht.readHumidity();.
- Leitura da temperatura com dht.readTemperature();.
- Verificação de falha na leitura usando isnan().
- Output: Exibição dos valores de temperatura e umidade no Serial Monitor.

 3. Sensor LDR

- Leitura de variações de luz sobre o sensor.
- Output: Valor da luminosidade é exibido no Serial Monitor.

4. Sensor HC-SR04 - Sensor ultrassom/proximidade

- Realiza e envio e captura de pulsos de 10 microssegundos, e calcula a distancia em centimetros (distancia = duracao * 0.034 / 2;)
- Baseado no calculo da distancia realiza o calculo de nivel de reserva de agua do reservatório de irrigação.
- Exibe mensagens sobre o estado do reservatório (em 6 estágios: Ótimo - acima de 90%, Bom - entre 90% e 75% , Normal - Entre 74% e 50%, Risco - entre 49% e 25%, Mínimo - entre 25% e 1%, Crítico - 0%);
- Output: Se a distância for inválida ou fora do alcance, exibe uma mensagem de erro, caso contrário, exibe o nível atual do reservatório.

 3. Relé de controle de irrigação

- implementação do controle do relé para ativar a irrigação com base nas condições ambientais conforme abaixo:
    **Variáveis e Parâmetros necessários e opcionais para acionamento da irrigação:
       Opcionais (significa que ao menos um dos itens itens deve satisfazer a condição imposta):
        a) Umidade Mínima: Umidade deve estar abaixo da umidadeMinima = 40.0; (Umidade mínima em porcentagem)
        b) Temperatura Máxima: Temperatura no sensor deve estar acima da temperatura Maxima aceitavel 30.0 (Temperatura máxima em Celsius).
       Necessários (significa que todos os itens devem satisfazer a condição imposta):
        c) Necessário: Nível Mínimo do Reservatório: Nivel deve estar acima do Nivel Minimo = 10000 (Nível mínimo de água necessário para ativar a irrigação).
        d) Limiar do LDR: O valor de captura do LDR deve estar abaixo do Limiar LDR (3000 que é o valor máximo do LDR para considerar que está escuro o suficiente para irrigar).

- Output: Com a satisfação da regra de automação, a mensagem de irrigação iniciada é exibida no Serial Monitor e LED verde do relé será acionado, se não o led vermelho se mantém acionado.

 Requisitos do Sistema

- ESP32 (Wokwi - esp32-devkit-c-v4) - https://wokwi.com
- Bibliotecas: HC-SR04, DHT sensor library e DHT22 (ver arquivo libraries.txt na pasta docs do repositório)

 Instruções de Uso

1. Para executar o código apenas inicie a simulação para ter acesso a solução de maneira interativa na plataforma Wokwi.

Se precisar de mais assistência ou encontrar problemas, consulte os documentos das bibliotecas ou entre em contato com o desenvolvedor responsável.

## 📁 Estrutura de pastas

Dentre os arquivos e pastas presentes na raiz do projeto, definem-se:

- <b>src</b>: Contém os codigos do projeto - Sketch.ino e diagram.json

- <b>docs</b>: Contém os documentos do projeto.
    - <b>README.md</b>: Informações gerais sobre o projeto, sobre a iniciativa e também instruções gerais para utilização do conteudo do repositório GIT.

- <b>tests</b>: Contém os resultados dos testes executados, para este projeto são prints do monitor serial da plataforma Wokwi com os resutados das simulações.

## 🔧 Como executar o código

1. Crie um projeto no ambiente wokwi utilizando a opção ESP32 e ESP 32 em Starter Templates;
2. Copie todo o conteudo do arquivo sketck.ino do repositório deste projeto no Github para a aba do projeto wokwi com o mesmo nome, sketch.ino;
3. Copie todo o conteudo do arquivo diagram.json do repositório deste projeto no Github para a aba do projeto wokwi com o mesmo nome, diagram.json;
4. Na aba Library Manager, no wokwi, clique no botão com o simbolo positivo (+) azul e adicione as bibliotecas de componentes: HC-SR04, DHT sensor library e DHT22 (para facilitar, copie e cole os nomes no popup que abrir em sua tela.)
5. Certifique-se de que todas as bibliotecas estão instaladas verificando se uma nova aba chamada libraries.txt foi criada com os nomes das bibliotecas acima.
6. Para iniciar a simulação apenas clique no botão verde com o simbolo de play na janela a direita do código da solução no wokwi.


## 🗃 Histórico de lançamentos
* 0.1.0 - 02/11/2024
    * 
* 0.X.0 - dd/10/2024
    *
* 0.X.0 - dd/10/2024
    * 
* 0.x.0 - 22/10/2024
    *

## 📋 Licença

<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1"><p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/agodoi/template">MODELO GIT FIAP</a> por <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://fiap.com.br">Fiap</a> está licenciado sobre <a href="http://creativecommons.org/licenses/by/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">Attribution 4.0 International</a>.</p>