#include "visitor.h"
#include<list>
#include<iostream>
#include<memory>

int main() {
	typedef std::unique_ptr<DocumentPart> PTR;
	typedef std::list<PTR> Document;
	Document document;

	document.push_back(PTR(new PlainText("Ovo je obican text, a ovo ")));
	document.push_back(PTR(new BoldText("je podebljan text")));
	document.push_back(PTR(new PlainText(", konacno ")));
	document.push_back(PTR(new Hyperlink("jedan hyperlink.", "web.math.hr")));

	HtmlVisitor *hv = new HtmlVisitor();
	for (Document::iterator it = document.begin(); it != document.end(); ++it)
		(*it)->accept(hv);

	std::cout << std::endl;
	LatexVisitor * lv = new LatexVisitor();
	for (Document::iterator it = document.begin(); it != document.end(); ++it)
		(*it)->accept(lv);

	std::cout << std::endl;
	return 0;
}
