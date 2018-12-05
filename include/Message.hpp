#ifndef MESSAGE_H
#define MESSAGE_H

class TextMessage{

	std::string _text;

public:

	TextMesage(const std::string& text) : _text(text);

	const& std::string text(){
		return _text;
	}
}



#endif