#include "lexer.h"

Lexer::Lexer(const std::string& text) :
	input(text), current_char(text[0])
{
	this->read_char();
	ac_automaton = new ACAutoMaton();

	// ��ʼ��AC�Զ����ڵ�
	{
		// �����
		{
			ac_automaton->add_key("+", TokenType::PLUS);
			ac_automaton->add_key("-", TokenType::MINUS);
			ac_automaton->add_key("*", TokenType::MUL);
			ac_automaton->add_key("/", TokenType::DIV);
			ac_automaton->add_key("=", TokenType::ASSIGN);
		}

		// ��ʶ��
		{
			ac_automaton->add_key("(", TokenType::LPAREN);
			ac_automaton->add_key(")", TokenType::RPAREN);
			ac_automaton->add_key(";", TokenType::SEMICOLON);
		}

		// ��������
		{
			ac_automaton->add_key("Int", TokenType::INT);
			ac_automaton->add_key("Float", TokenType::FLOAT);
			ac_automaton->add_key("Bool", TokenType::BOOL);
			ac_automaton->add_key("Void", TokenType::VOID);
			ac_automaton->add_key("Func", TokenType::FUNC);
            ac_automaton->add_key("Str", TokenType::STRING);
		}

		// �������޹̶���̬

        // �߼�����
        {
            ac_automaton->add_key("Player", TokenType::PLAYER);
            ac_automaton->add_key("State", TokenType::STATE);
            ac_automaton->add_key("Card", TokenType::CARD);
            ac_automaton->add_key("CardContainer", TokenType::CARD_CONTAINER);
        }
	}
}

Lexer::~Lexer() {
    delete ac_automaton; // �ͷ�AC�Զ���
}

Token Lexer::get_next_token()
{
	std::string buffer;
	TokenType type = TokenType::UNKNOWN;

	// �����ո�
	while (isspace(current_char))
		this->read_char();

    // ����ע��
    if (current_char == '#') {
        while (current_char != '\n' && current_char != 0) {
            this->read_char();
        }
        return get_next_token(); // ������ȡ��һ�����
    }

    // �����ַ���
    if (current_char == '"' || current_char == '\'') {
        char quote_char = current_char;
        this->read_char();
        while (current_char != quote_char && current_char != 0) {
            buffer.push_back(current_char);
            this->read_char();
        }
        if (current_char == quote_char) {
            this->read_char();
            return Token(TokenType::STRING, buffer);
        }
        else {
            std::cerr << "Error: ��ƥ����ַ���" << std::endl;
            return Token(TokenType::UNKNOWN, buffer);
        }
    }

    // ���Զ�ȡ���ַ����
    if (isalpha(current_char) || current_char == '_')
    {
        while (isalpha(current_char) || current_char == '_' || isdigit(current_char))
        {
            buffer.push_back(current_char);
            this->read_char();
        }
        type = ac_automaton->find_key(buffer); // ʹ��AC�Զ������ҹؼ���
        if (type == TokenType::UNKNOWN)
        {
            return Token(TokenType::IDENTIFIER, buffer); // �����ʶ��
        }
    }
    // ��������
    else if (isdigit(current_char)) {
        // ��ȡ��������
        do {
            buffer.push_back(current_char);
            this->read_char();
        } while (isdigit(current_char));

        // ����С����
        if (current_char == '.') {
            buffer.push_back(current_char);
            this->read_char();
            while (isdigit(current_char)) {
                buffer.push_back(current_char);
                this->read_char();
            }
            return Token(TokenType::FLOAT, buffer); // ���ظ�����
        }

        return Token(TokenType::INTEGER, buffer); // ��������
    }
    // ��ӷֺŴ���
    else if (current_char == ';')
    {
        this->read_char();
        return Token(TokenType::SEMICOLON, ";");
    }
    // �����ַ����������������
    else {
        switch (current_char){
        case '+':
            this->read_char();
            return Token(TokenType::PLUS, "+");
        case '-':
            this->read_char();
            return Token(TokenType::MINUS, "-");
        case '*':
            this->read_char();
            return Token(TokenType::MUL, "*");
        case '/':
            this->read_char();
            return Token(TokenType::DIV, "/");
        case '(':
            this->read_char();
            return Token(TokenType::LPAREN, "(");
        case ')':
            this->read_char();
            return Token(TokenType::RPAREN, ")");
        case '=':
            buffer.push_back(current_char);
            this->read_char();
            if (current_char == '=')
            {
                buffer.push_back(current_char);
                this->read_char();
                return Token(TokenType::EQUAL, "==");
            }
            else
            {
                return Token(TokenType::ASSIGN, "=");
            }
        default:
            if (current_char != 0)
                std::cerr << "Unknown Token '" << current_char << "'" << std::endl;
            this->read_char();
            return Token(TokenType::UNKNOWN, buffer);
        }
    }

    // ����������token�󣬷��ؽ���״̬
    if (current_char == 0)
        return Token(TokenType::EOF_TOKEN, "");

    return Token(type, buffer);
}

void Lexer::read_char()
{
	current_char = (read_position >= input.length()) ? 0 : input[read_position];
	position = read_position++;
}

