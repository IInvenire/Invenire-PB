# INVENIRE — Requisitos não funcionais e arquitetura



Sistema digital de achados e perdidos • UNICAP
Grupo: Ivenire
Integrantes: Isaac Fotes, Giovanna Pessoa, Fernando Lucas e Eduardo Garcia
Data: 19/10/2026

## 1. Objetivo e escopo

Classificar os requisitos não funcionais (RNFs) do INVENIRE e relacioná-los às histórias existentes no backlog e às decisões de arquitetura. O sistema centraliza o cadastro e a pesquisa de objetos perdidos e encontrados em ambientes como universidades e empresas.

O MVP contempla autenticação, cadastro de objetos, busca e filtros (US01 a US05). Detalhes, confirmação de recuperação e histórico (US06 a US08) são Should Have no backlog. A US04 depende da abertura de detalhes; a equipe deverá planejar a visualização mínima necessária junto à busca. Chat, notificações, match automático e área empresarial não integram o escopo obrigatório deste documento.

As metas quantitativas são propostas de aceite para validação pela equipe. Os testes descritos ainda deverão ser executados; não constituem resultados obtidos. Os IDs RNF deste documento pertencem ao projeto INVENIRE.

## 2. Histórias existentes e rastreabilidade

| ID / Issue | História resumida | Prioridade |
| --- | --- | --- |
| US01 / #1 | Como usuário, quero realizar login para acessar a plataforma de forma identificada. | Must Have |
| US02 / #2 | Como usuário que perdeu um objeto, quero cadastrá-lo para aumentar minhas chances de encontrá-lo. | Must Have |
| US03 / #3 | Como usuário que encontrou um objeto, quero cadastrá-lo para ajudar o proprietário. | Must Have |
| US04 / #4 | Como usuário, quero pesquisar itens para verificar se meu objeto foi encontrado. | Must Have |
| US05 / #5 | Como usuário, quero aplicar filtros para encontrar itens relevantes mais rapidamente. | Must Have |
| US06 / #6 | Como usuário, quero visualizar detalhes para verificar a correspondência do objeto. | Should Have |
| US07 / #7 | Como proprietário, quero marcar meu item como recuperado. | Should Have |
| US08 / #8 | Como usuário, quero visualizar meu histórico de objetos. | Should Have |



## 3. RNFs de desempenho e segurança

### RNF-01 | Desempenho • tempo de resposta

Prioridade: Alta • Histórias: US04, US05, US06

Requisito: 95% das consultas de busca, filtros e detalhes devem responder em até 2 segundos na API, com 20 usuários simultâneos e 10 mil itens. Erros de servidor devem ficar abaixo de 1%.

Verificação: Carga de 10 minutos, após 1 minuto de aquecimento, com uma consulta por usuário a cada 5 segundos. Medir p95 e erros.

### RNF-02 | Desempenho • capacidade

Prioridade: Alta • Histórias: US02, US03, US06

Requisito: Aceitar uma foto opcional JPEG ou PNG de até 5 MB e 12 megapixels por item. Após o término do recebimento, 95% dos cadastros devem confirmar persistência em até 3 segundos, com cinco envios simultâneos. A ausência de foto não deve impedir o cadastro.

Verificação: Testar cadastros sem foto, com foto dentro dos limites e acima deles; medir o prazo somente após o upload completo.

### RNF-03 | Segurança • autenticação e autorização

Prioridade: Alta • Histórias: US01, US02, US03, US07, US08

Requisito: Toda criação de item deve exigir sessão válida e vincular o autor no servidor. Alterações de status e histórico pessoal devem verificar o vínculo com o usuário, sem confiar no identificador enviado pelo navegador. Nenhuma tentativa não autorizada deve ser aceita.

Verificação: Testar sessão ausente, expirada e dois usuários distintos; chamar a API diretamente e trocar IDs. A política de autorização da US07 deve ser aprovada antes de sua implementação.

### RNF-04 | Segurança • confidencialidade

Prioridade: Alta • Histórias: US01 a US08

Requisito: Todo tráfego autenticado deve usar HTTPS; senhas devem ser armazenadas apenas como hash com salt. Busca e detalhes não devem retornar e-mail, senha, token ou telefone do autor. Logs não devem registrar senhas, tokens ou conteúdo integral das requisições.

Verificação: Inspecionar conexão, estrutura de armazenamento de senha, respostas da API e logs com dados fictícios conhecidos.

### RNF-05 | Segurança • resistência a abuso

Prioridade: Alta • Histórias: US01, US02, US03

Requisito: Após cinco falhas de login em 15 minutos por conta, aplicar bloqueio temporário de novas tentativas por 15 minutos; limitar também a 30 tentativas por IP em 15 minutos. Rejeitar arquivos que não sejam imagens válidas e impedir sua execução.

Verificação: Testar limites e expiração, mensagens sem revelar se a conta existe, extensão falsa, arquivo corrompido e imagem fora dos limites.

## 4. RNFs de usabilidade e confiabilidade

### RNF-06 | Usabilidade • aprendizagem

Prioridade: Alta • Histórias: US01, US02, US03, US04, US05

Requisito: Pelo menos quatro de cinco usuários representativos, no primeiro uso e sem auxílio, devem entrar com conta de teste, cadastrar um item sem foto e realizar uma busca com filtro em até cinco minutos.

Verificação: Aplicar roteiro idêntico com estudantes e profissionais; registrar tempo, sucesso e dificuldades de cada participante.

### RNF-07 | Usabilidade • acessibilidade e adaptação

Prioridade: Alta • Histórias: US01 a US08

Requisito: Os fluxos implementados devem funcionar por teclado, com foco visível, campos rotulados, erros textuais junto ao campo e informações que não dependam apenas de cor. Entre 360 e 1440 pixels de largura não deve haver perda de controles essenciais.

Verificação: Executar fluxos por teclado; conferir telas em 360, 768 e 1440 pixels. Verificar mensagens de erro e estados vazio, carregando e falha.

### RNF-08 | Confiabilidade • integridade

Prioridade: Alta • Histórias: US02, US03, US07, US08

Requisito: Um cadastro confirmado deve persistir item e vínculo do autor. Repetir a mesma requisição de cadastro com a mesma chave de idempotência, por até 24 horas, não deve criar outro item. Atualizações concorrentes de status não devem produzir estados incompatíveis.

Verificação: Simular timeout seguido de reenvio, falha antes do commit e duas alterações simultâneas; verificar ausência de duplicação e consistência do estado.

### RNF-09 | Confiabilidade • recuperabilidade

Prioridade: Alta • Histórias: US01 a US08

Requisito: Executar backup diário do banco e das imagens, manter sete dias de cópias e restaurar o conjunto em até quatro horas em ensaio, com perda máxima de 24 horas de dados.

Verificação: Restaurar em ambiente isolado; verificar usuários, vínculos, itens e imagens, registrando tempos e ponto recuperado.

### RNF-10 | Segurança • responsabilização

Prioridade: Alta • Histórias: US02, US03, US07, US08

Requisito: Registrar criação de item e mudanças de status com ID do item, ator, data/hora UTC e resultado; em mudanças, incluir estado anterior e novo. A conta da aplicação não deve alterar nem excluir eventos registrados.

Verificação: Confrontar eventos com um fluxo completo e tentar modificar registros usando a conta da aplicação. Não incluir dados pessoais desnecessários no histórico técnico.

Condições das metas de desempenho: homologação com 2 vCPUs, 4 GB de RAM, SSD e rede estável. Executar cenários isolados e combinados; resultados dependem da implementação e devem orientar ajustes de capacidade. Para histórias Should Have, aplicar os RNFs quando a funcionalidade entrar na versão.

## 5. Decisões arquiteturais propostas

### DA-01 | Backend como monólito modular

Motivada por: RNF-01, RNF-03, RNF-08

Decisão: Separar módulos de autenticação, itens, pesquisa e auditoria dentro de uma aplicação, com interface web e API. Manter regras de negócio no servidor e contratos entre módulos.

Justificativa e consequências: A solução atende ao MVP com menor custo operacional que serviços distribuídos. A separação permite evoluir o produto sem misturar autenticação e cadastro. Custo: o backend compartilha implantação e capacidade; o desempenho precisa ser medido.

### DA-02 | Banco relacional e pesquisa paginada

Motivada por: RNF-01, RNF-08

Decisão: Persistir usuários, itens, referências de imagens e eventos em banco relacional. Usar chaves estrangeiras, índices nos campos usados por filtros e estratégia de índice textual para busca por nome, conforme o banco escolhido. Paginar resultados em até 20 itens e devolver somente os campos necessários.

Justificativa e consequências: Índices e paginação limitam leitura e tamanho das respostas; transações preservam vínculos. Um índice simples não resolve toda busca por trecho: a consulta real deve ser medida. Custo: índices ocupam espaço e tornam escritas mais caras.

### DA-03 | Controle de acesso no servidor e sessão protegida

Motivada por: RNF-03, RNF-04, RNF-05

Decisão: Verificar sessão e permissão por objeto em cada operação protegida. Usar HTTPS, cookies Secure, HttpOnly e SameSite, proteção CSRF e hash de senha por biblioteca apropriada, como Argon2id. Centralizar limites de tentativas em armazenamento compartilhado.

Justificativa e consequências: A proteção precisa valer mesmo com chamadas diretas à API. Hashes reduzem exposição de senhas e a limitação dificulta tentativas repetidas. Custo: bloqueios podem afetar usuários legítimos; oferecer mensagem genérica e informar o tempo de espera.

### DA-04 | Imagens separadas do banco e validadas

Motivada por: RNF-02, RNF-04, RNF-05

Decisão: Guardar imagens em armazenamento de objetos privado e metadados no banco. Validar formato por decodificação, tamanho e dimensões; recodificar a imagem e remover metadados EXIF. Usar nomes internos gerados, servir por acesso controlado e gerar miniaturas.

Justificativa e consequências: Fotos grandes não devem sobrecarregar consultas nem expor localização embutida. Limites reduzem consumo e rejeitam entradas incompatíveis. Custo: é necessário manter consistência entre banco e armazenamento; limpar imagens temporárias quando o cadastro falhar.

## 6. Decisões e solução resultante

### DA-05 | Componentes de interface reutilizáveis

Motivada por: RNF-06, RNF-07

Decisão: Construir formulários responsivos com rótulos, foco visível e mensagens por campo. Sinalizar foto opcional, confirmar cadastro e preservar campos preenchidos quando houver erro. Reutilizar cartões de itens, busca e filtros.

Justificativa e consequências: Consistência reduz reaprendizagem e erros. Feedback explica o que ocorreu e como corrigir. Custo: componentes ainda exigem testes com usuários e inspeção por teclado.

### DA-06 | Transações, idempotência e auditoria

Motivada por: RNF-08, RNF-10

Decisão: Persistir item e evento de criação na mesma transação. Associar a chave de idempotência ao usuário, conteúdo e resultado da operação, com unicidade por 24 horas. Usar versão do registro nas mudanças de status; gravações concorrentes devem falhar com mensagem de atualização necessária. Restringir a conta da aplicação a inserção/leitura de eventos.

Justificativa e consequências: Reenvios de rede não devem gerar itens duplicados; conflitos não podem sobrescrever decisões silenciosamente. Eventos vinculados às transações permitem reconstruir alterações. Custo: armazenamento de chaves e eventos, limpeza programada e tratamento explícito de conflitos.

### DA-07 | Backup coordenado e recuperação ensaiada

Motivada por: RNF-09

Decisão: Agendar cópias do banco e das imagens em destino separado e protegido. Usar manifesto dos arquivos e ponto de recuperação do banco; reter sete dias e documentar o procedimento de restauração.

Justificativa e consequências: Restaurar apenas o banco pode produzir itens sem imagem. O ensaio confirma a possibilidade real de recuperar o conjunto. Custo: espaço adicional e tempo para ensaios; backup não garante disponibilidade contínua.

## Solução proposta

Interface web responsiva → API modular → banco relacional para usuários, itens e eventos. A API também acessa o armazenamento privado de imagens. Sessões e limites de tentativa são verificados no servidor; uma rotina operacional realiza backup do conjunto. Linguagem, framework e hospedagem serão escolhidos pela equipe conforme o atendimento às metas.

O MVP não exige mecanismo de match, chat em tempo real nem microsserviços. Se esses recursos forem priorizados futuramente, seus RNFs deverão ser levantados e a arquitetura reavaliada. As decisões acima são propostas, não declarações de implementação concluída.

## 7. Matriz de rastreabilidade

| RNF | Classificação | Histórias / Issues | Decisões |
| --- | --- | --- | --- |
| 01 | Desempenho | US04–US06 / #4–#6 | DA-01, DA-02 |
| 02 | Desempenho | US02, US03, US06 / #2, #3, #6 | DA-04 |
| 03 | Segurança | US01–US03, US07, US08 | DA-01, DA-03 |
| 04 | Segurança | US01–US08 / #1–#8 | DA-03, DA-04 |
| 05 | Segurança | US01–US03 / #1–#3 | DA-03, DA-04 |
| 06 | Usabilidade | US01–US05 / #1–#5 | DA-05 |
| 07 | Usabilidade | US01–US08 / #1–#8 | DA-05 |
| 08 | Confiabilidade | US02, US03, US07, US08 | DA-01, DA-02, DA-06 |
| 09 | Confiabilidade | US01–US08 / #1–#8 | DA-07 |
| 10 | Segurança / auditoria | US02, US03, US07, US08 | DA-06 |

Em todas as linhas, USxx corresponde à Issue de mesmo número. Histórias posteriores mantêm a prioridade original; esta matriz não altera o backlog.

## 8. Conexão entre necessidade e solução

US04 e US05 → RNF-01 → DA-02: localizar objetos rapidamente requer respostas previsíveis; a solução usa índices apropriados, filtros no servidor e paginação.

US07 e US08 → RNF-03 → DA-03: alterar o status e consultar histórico pessoal exige autorização; o backend verifica o usuário e o vínculo com o registro.

US02 e US03 → RNF-06 e RNF-07 → DA-05: cadastrar objetos de forma simples exige formulários claros, foto opcional e retorno acessível sobre erros e sucesso.

## 9. Validação antes da entrega

A equipe deverá aprovar metas, política de visibilidade dos itens e autorização da US07, executar testes e registrar por RNF: ambiente, data, responsável, resultado e evidência. Falhas devem gerar ajustes na implementação ou revisão justificada das metas. Um integrante realizará o envio do material completo.


