/*
 * visitor.h
 *
 *  Created on: 12. svi 2015.
 *      Author: Tomislav
 */

#ifndef SRC_VISITOR_H_
#define SRC_VISITOR_H_

#include<string>

class Visitor;

class Visitable {
public:
	virtual void accept(Visitor *) = 0;
	virtual ~Visitable() {
	}
};

class DocumentPart: public Visitable {
public:
	DocumentPart(std::string text) :
			m_text(text) {
	}
	std::string get_text() {
		return m_text;
	}
	virtual ~DocumentPart() {
	}
private:
	std::string m_text;
};

class PlainText: public DocumentPart {
public:
	PlainText(std::string text) :
			DocumentPart(text) {
	}
	void accept(Visitor *);
};

class BoldText: public DocumentPart {
public:
	BoldText(std::string text) :
			DocumentPart(text) {
	}
	void accept(Visitor *);
};

class Hyperlink: public DocumentPart {
public:
	Hyperlink(std::string text, std::string url) :
			DocumentPart(text), m_url(url) {
	}
	std::string get_url() {
		return m_url;
	}
	void accept(Visitor *);
private:
	std::string m_url;
};

class Visitor {
public:
	virtual void visit(PlainText *) = 0;
	virtual void visit(BoldText *) = 0;
	virtual void visit(Hyperlink *) = 0;
	virtual ~Visitor() {
	}
};

class HtmlVisitor: public Visitor {
public:
	void visit(PlainText *);
	void visit(BoldText *);
	void visit(Hyperlink *);
};

class LatexVisitor: public Visitor {
public:
	void visit(PlainText *);
	void visit(BoldText *);
	void visit(Hyperlink *);
};

#endif /* SRC_VISITOR_H_ */
