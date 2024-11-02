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

 3. XXXXXXXXXXXX

XXXXXXXXXXXXXXXXX

- Output: XXXXXXXXXXX

 Requisitos do Sistema

- ESP32 (Wokwi - esp32-devkit-c-v4) - https://wokwi.com
- Bibliotecas: DHT sensor library e DHT22 (ver arquivo libraries.txt na pasta docs do repositório)

 Instruções de Uso

1. Certifique-se de que todas as bibliotecas estão instaladas.
2. Configure os parametros de conexão do banco de dados no arquivo conexao.txt no diretorio raiz da aplicação.
3. Execute `main.py` para iniciar o aplicativo e siga as instruções no menu.

Se precisar de mais assistência ou encontrar problemas, consulte os documentos das bibliotecas ou entre em contato com o desenvolvedor responsável.

## 📁 Estrutura de pastas

Dentre os arquivos e pastas presentes na raiz do projeto, definem-se:

- <b>src</b>: Contém os codigos do projeto - Sketch.ino e diagram.json

- <b>docs</b>: Contém os documentos do projeto.
    - <b>README.md</b>: Informações gerais sobre o projeto, sobre a iniciativa e também instruções gerais para utilização do conteudo do repositório GIT.

- <b>tests</b>: Contém os resultados dos testes executados, para este projeto são prints do monitor serial da plataforma Wokwi com os resutados das simulações.

## 🔧 Como executar o código

1. Para executar o código apenas inicie a simulação para ter acesso a solução de maneira interativa na plataforma Wokwi.

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