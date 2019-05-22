#include <stdio.h>
#include <string.h>

typedef unsigned char bool; /* Real type */
typedef unsigned int uint32_t; /* Real type, normally in <stdint.h>, a good practice to use it */

typedef enum
  {
    TOKEN_EAT, //0
    TOKEN_DQ, //1
    TOKEN_SQ, //2
    TOKEN_SEMI, //3
    TOKEN_DBL_SEMI, //4
    TOKEN_OPERATOR, //5
    TOKEN_NEG, //6
    TOKEN_DBLAND, //7
    TOKEN_DBLOR, //8
    TOKEN_PIPE, //9
    TOKEN_OP_ARITHM, //10
    TOKEN_AND, //11
    TOKEN_OP_BRA, //12
    TOKEN_CL_BRA, //13
    TOKEN_OP_PAR, //14
    TOKEN_CL_PAR, //15
    TOKEN_REDIR, //16
    TOKEN_ASS_WORD, //17
    TOKEN_OP_CMD, //18
    TOKEN_OP_CURLY, //19
    TOKEN_CL_CURLY, //20
    TOKEN_EQUAL, //20
    TOKEN_STRING,
    TOKEN_NAME,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_NULL
  } e_token_type;

typedef struct
{
  const char* op;
  uint32_t size;
  e_token_type type;
} t_oplist;

typedef struct
{
  char content[128]; /* Replace with a dynamic array */
  uint32_t size;
  e_token_type type;
} t_lexer_token;

typedef struct
{
  t_lexer_token tokens[2048];  /* Replace with a dynamic array */
  uint32_t size;
} t_lexer;

static const t_oplist existing_token[] =
  {
    {"while", 5, TOKEN_WHILE}, /* Sort by size, for obvious reason ! */
    {"$((", 3, TOKEN_OP_ARITHM},
    {">>-", 3, TOKEN_REDIR},
    {"for", 3, TOKEN_FOR},
    {"$(", 2, TOKEN_OP_CMD},
    {"${", 2, TOKEN_OP_CURLY},
    {">>", 2, TOKEN_REDIR},
    {"<<", 2, TOKEN_REDIR},
    {"||", 2, TOKEN_DBLOR},
    {">|", 2, TOKEN_REDIR},
    {"<>", 2, TOKEN_REDIR},
    {"<&", 2, TOKEN_REDIR},
    {">&", 2, TOKEN_REDIR},
    {"&&", 2, TOKEN_DBLAND},
    {"{ ", 2, TOKEN_OP_BRA},
    {"{\n", 2, TOKEN_OP_BRA},
    {"{\v", 2, TOKEN_OP_BRA},
    {"{\t", 2, TOKEN_OP_BRA},
    {"{\r", 2, TOKEN_OP_BRA},
    {"{\f", 2, TOKEN_OP_BRA},
    {" {", 2, TOKEN_CL_BRA},
    {"\n{", 2, TOKEN_CL_BRA},
    {"\v{", 2, TOKEN_CL_BRA},
    {"\t{", 2, TOKEN_CL_BRA},
    {"\r{", 2, TOKEN_CL_BRA},
    {"\f{", 2, TOKEN_CL_BRA},
    {";;", 2, TOKEN_DBL_SEMI},
    {"! ", 2, TOKEN_NEG},
    {"}", 1, TOKEN_CL_BRA},
    {"|", 1, TOKEN_PIPE},
    {"&", 1, TOKEN_AND},
    {"(", 1, TOKEN_OP_PAR},
    {")", 1, TOKEN_CL_PAR},
    {">", 1, TOKEN_REDIR},
    {"<", 1, TOKEN_REDIR},
    {"(", 1, TOKEN_OP_PAR},
    {")", 1, TOKEN_CL_PAR},
    {"{", 1, TOKEN_OP_CURLY},
    {"}", 1, TOKEN_CL_CURLY},
    {";", 1, TOKEN_SEMI},
    {" ", 1, TOKEN_EAT},
    {"\n", 1, TOKEN_EAT},
    {"\v", 1, TOKEN_EAT},
    {"\t", 1, TOKEN_EAT},
    {"\r", 1, TOKEN_EAT},
    {"\f", 1, TOKEN_EAT},
    {"=", 1, TOKEN_EQUAL},
    {NULL, 1, 0}
  };

void addToLexer(t_lexer* lexer, const char* text, uint32_t text_size, e_token_type type)
{
  t_lexer_token item;
  strncpy(item.content, text, text_size);
  item.content[text_size] = 0;
  item.size = text_size;
  item.type = type;
  lexer->tokens[lexer->size] = item;
  ++lexer->size;
}

t_oplist searchTokenType(const char* s)
{
  const t_oplist* ex_tok = existing_token;
  t_oplist not_found = {0, 0, 0};

  while (ex_tok && ex_tok->op)
  {
    if (strncmp(s, ex_tok->op, ex_tok->size) == 0)
      return *ex_tok;
    ++ex_tok;
  }

  return not_found;
}

bool fillLexerFromString(const char* s, t_lexer* lexer)
{
  t_oplist current;
  const char* prev = s; /* Previous time we encountered a known token. */

  while (s && *s)
  {
    /* Handle \\ escaping */
    if (*s == '\\')
    {
      ++s;
      continue;
    }

    /* Search any know token */
    current = searchTokenType(s);
    /*
       if current.type == TOKEN_OP_*
       add +1 a counter !
       if current.type == TOKEN_CL_*
       dec -1 a counter !
       At the end, check if the counter is equal to 0.
       If not, there is a syntax error!
    */

    /* Find another token ? let's see if we have something inbetween */
    if ((current.op != 0 || *s == '"' || *s == '\'') && prev != s)
	{
		printf("s:%s\n", s);
		printf("prev: %s\n", prev);
		addToLexer(lexer, prev, s - prev, TOKEN_NAME);
	}

    /* Token found */
    if (current.op != 0)
    {
      s += current.size;
      if (current.type != TOKEN_EAT)
        addToLexer(lexer, current.op, current.size, current.type);
      prev = s;
    }
    /* Token not found, but could be an escaped string */
    else if (*s == '"' || *s == '\'')
    {
      /* handleEscaping(); Handle it for real */
      ++s;
      while (*s && *s != '\'' && *s != '"') /* <- dumb function */
        ++s;
      if (!*s || (*s != '\'' && *s != '"'))
      {
        /* string not finished! */
        return 0;
      }
      ++s;
    }
    else
	{
		++s;
		printf("a\n");
	}
  }

  /* Handle what's remain at the end of the input */
  if (prev != s)
    addToLexer(lexer, prev, s - prev, TOKEN_NAME);

  return 1;
}

void print(const t_lexer* lexer)
{
  uint32_t i = 0;

  for (i = 0; i < lexer->size; ++i)
    printf("<%s (%i)> ", lexer->tokens[i].content, lexer->tokens[i].type);
  printf("\n");
}

int main()
{
  const char* cmd = "ec\\ho'aaaa' lol";

  t_lexer lexer;
  lexer.size = 0;
  if (!fillLexerFromString(cmd, &lexer))
    printf("Syntax error !\n");

  print(&lexer);

  return 0;
}
