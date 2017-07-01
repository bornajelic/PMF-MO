/*
 * visitor.cpp
 *
 *  Created on: 12. svi 2015.
 *      Author: Tomislav
 */

#include "visitor.h"

#include<iostream>

void PlainText::accept(Visitor *visitor) {
	visitor->visit(this);
}

void BoldText::accept(Visitor *visitor) {
	visitor->visit(this);
}

void Hyperlink::accept(Visitor *visitor) {
	visitor->visit(this);
}

void write_plain(std::string text) {
	std::cout << text;
}

void write_bold(std::string open_tag, std::string text,
		std::string closed_tag) {
	std::cout << open_tag << text << closed_tag;
}

void write_link(std::string open_tag, std::string url_text,
		std::string tag_int_the_middle, std::string text,
		std::string closed_tag) {
	std::cout << open_tag << url_text << tag_int_the_middle << text
			<< closed_tag;
}

void HtmlVisitor::visit(PlainText *plain_text) {
	write_plain(plain_text->get_text());
}

void HtmlVisitor::visit(BoldText *bold_text) {
	write_bold("<b>", bold_text->get_text(), "</b>");
}

void HtmlVisitor::visit(Hyperlink *hyperlink) {
	write_link("<a href=\"", hyperlink->get_url(), "\">", hyperlink->get_text(),
			"</a>");
}

void LatexVisitor::visit(PlainText *plain_text) {
	write_plain(plain_text->get_text());
}

void LatexVisitor::visit(BoldText *bold_text) {
	write_bold("{\\bf", bold_text->get_text(), "}");
}

void LatexVisitor::visit(Hyperlink *hyperlink) {
	write_link("\\href{", hyperlink->get_url(), "}{", hyperlink->get_text(),
			"}");
}
