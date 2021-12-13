#include "pch.hpp"
#include "main_form.hpp"
using namespace xtd;
using namespace xtd::forms;
using namespace xtd_dev_tools;

main_form::main_form() {
	menu(m_main_menu);

	text("XTD Dev Tools");
	client_size({ 640, 480 });
  minimum_size(client_size()).maximum_size(client_size());

	// 
	static std::vector<std::unique_ptr<button>> buttons{};
	std::int32_t yoffset = 10;
	std::int32_t xoffset = 10;
	for(const auto& v : m_tools_menu_item_options.menu_items())
	{
		std::unique_ptr<button> btn{ new button() };
		btn->parent(*this)
			.size({ 100, 45 })
			.location({ (client_size().width() - btn->size().width()) / 2, yoffset })
			.text(v.get().text())
			.click += [&v] {
					v.get().perform_click();
			};
		buttons.emplace_back(std::move(btn));
		yoffset += 51;
		//xoffset += 51;
	}
}

void main_form::main() {
	const std::unique_ptr<main_form> main_form_ptr(new main_form());
	application::run(*main_form_ptr);
}
