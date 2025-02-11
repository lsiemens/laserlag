DOCS_DIR = doc
BUILD_DIR = build

test: $(BUILD_DIR)
	cd $(BUILD_DIR); ctest

$(BUILD_DIR):
	mkdir $(BUILD_DIR) -p
	cd $(BUILD_DIR); cmake ..
	cd $(BUILD_DIR); make

$(DOCS_DIR)/html:
	cd $(DOCS_DIR); doxygen Doxyfile

$(DOCS_DIR)/latex:
	cd $(DOCS_DIR); doxygen Doxyfile

open_docs: $(DOCS_DIR)/html
	open $(DOCS_DIR)/html/index.html

clean:
	rm $(BUILD_DIR) -rf
	rm $(DOCS_DIR)/html -rf
	rm $(DOCS_DIR)/latex -rf

.PHONY: test open_docs clean
