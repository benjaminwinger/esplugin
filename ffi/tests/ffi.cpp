#include <cassert>
#include <cstdio>
#include <cstring>

#include "esplugin.h"

void test_game_id_values() {
  printf("testing ESP_GAME_* values...\n");
  assert(ESP_GAME_OBLIVION == 0);
  assert(ESP_GAME_SKYRIM == 1);
  assert(ESP_GAME_FALLOUT3 == 2);
  assert(ESP_GAME_FALLOUTNV == 3);
  assert(ESP_GAME_MORROWIND == 4);
  assert(ESP_GAME_FALLOUT4 == 5);
  assert(ESP_GAME_SKYRIMSE == 6);
}

void test_esp_plugin_new() {
  printf("testing esp_plugin_new()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "foo");
  assert(return_code == ESP_OK);

  esp_plugin_free(plugin);
}

void test_esp_plugin_parse() {
  printf("testing esp_plugin_parse()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "../../testing-plugins/Skyrim/Data/Blank.esm");
  assert(return_code == ESP_OK);

  return_code = esp_plugin_parse(plugin, true);
  assert(return_code == ESP_OK);

  esp_plugin_free(plugin);
}

void test_esp_plugin_filename() {
  printf("testing esp_plugin_new()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "foo");
  assert(return_code == ESP_OK);

  char * filename;
  return_code = esp_plugin_filename(plugin, &filename);
  assert(return_code == ESP_OK);
  assert(strcmp(filename, "foo") == 0);

  esp_string_free(filename);
  esp_plugin_free(plugin);
}

void test_esp_plugin_masters() {
  printf("testing esp_plugin_masters()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "../../testing-plugins/Skyrim/Data/Blank - Master Dependent.esm");
  assert(return_code == ESP_OK);

  return_code = esp_plugin_parse(plugin, true);
  assert(return_code == ESP_OK);

  char ** masters;
  uint8_t num_masters;
  return_code = esp_plugin_masters(plugin, &masters, &num_masters);
  assert(return_code == ESP_OK);
  assert(num_masters == 1);
  assert(strcmp(masters[0], "Blank.esm") == 0);

  esp_string_array_free(masters, num_masters);
  esp_plugin_free(plugin);
}

void test_esp_plugin_is_master() {
  printf("testing esp_plugin_is_master()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "../../testing-plugins/Skyrim/Data/Blank.esm");
  assert(return_code == ESP_OK);

  return_code = esp_plugin_parse(plugin, true);
  assert(return_code == ESP_OK);

  bool is_master;
  return_code = esp_plugin_is_master(plugin, &is_master);
  assert(return_code == ESP_OK);
  assert(is_master);

  esp_plugin_free(plugin);
}

void test_esp_plugin_is_light_master() {
  printf("testing esp_plugin_is_light_master()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_FALLOUT4, "../../testing-plugins/Skyrim/Data/Blank.esl");
  assert(return_code == ESP_OK);

  bool is_light_master;
  return_code = esp_plugin_is_light_master(plugin, &is_light_master);
  assert(return_code == ESP_OK);
  assert(is_light_master);

  esp_plugin_free(plugin);
}

void test_esp_plugin_is_valid() {
  bool is_valid;
  auto return_code = esp_plugin_is_valid(ESP_GAME_SKYRIM, "../../testing-plugins/Skyrim/Data/Blank.esm", true, &is_valid);
  assert(return_code == ESP_OK);
  assert(is_valid);
}

void test_esp_plugin_description() {
  printf("testing esp_plugin_description()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "../../testing-plugins/Skyrim/Data/Blank.esm");
  assert(return_code == ESP_OK);

  return_code = esp_plugin_parse(plugin, true);
  assert(return_code == ESP_OK);

  char * description;
  return_code = esp_plugin_description(plugin, &description);
  assert(return_code == ESP_OK);
  assert(strcmp(description, "v5.0") == 0);

  esp_string_free(description);
  esp_plugin_free(plugin);
}

void test_esp_plugin_header_version() {
  printf("testing esp_plugin_header_version()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "../../testing-plugins/Skyrim/Data/Blank.esm");
  assert(return_code == ESP_OK);

  return_code = esp_plugin_parse(plugin, true);
  assert(return_code == ESP_OK);

  float version;
  return_code = esp_plugin_header_version(plugin, &version);
  assert(return_code == ESP_OK);
  assert(version == 0.94f);

  esp_plugin_free(plugin);
}

void test_esp_plugin_is_empty() {
  printf("testing esp_plugin_is_empty()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "../../testing-plugins/Skyrim/Data/Blank.esm");
  assert(return_code == ESP_OK);

  return_code = esp_plugin_parse(plugin, true);
  assert(return_code == ESP_OK);

  bool is_empty;
  return_code = esp_plugin_is_empty(plugin, &is_empty);
  assert(return_code == ESP_OK);
  assert(!is_empty);

  esp_plugin_free(plugin);
}

void test_esp_plugin_count_override_records() {
  printf("testing esp_plugin_count_override_records()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "../../testing-plugins/Skyrim/Data/Blank.esm");
  assert(return_code == ESP_OK);

  return_code = esp_plugin_parse(plugin, true);
  assert(return_code == ESP_OK);

  size_t count;
  return_code = esp_plugin_count_override_records(plugin, &count);
  assert(return_code == ESP_OK);
  assert(count == 0);

  esp_plugin_free(plugin);
}

void test_esp_plugin_do_records_overlap() {
  printf("testing esp_plugin_do_records_overlap()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIM, "../../testing-plugins/Skyrim/Data/Blank.esm");
  assert(return_code == ESP_OK);

  return_code = esp_plugin_parse(plugin, false);
  assert(return_code == ESP_OK);

  bool overlap;
  return_code = esp_plugin_do_records_overlap(plugin, plugin, &overlap);
  assert(return_code == ESP_OK);
  assert(overlap);

  esp_plugin_free(plugin);
}

void test_esp_plugin_is_valid_as_light_master() {
  printf("testing esp_plugin_is_valid_as_light_master()...\n");
  Plugin * plugin;
  auto return_code = esp_plugin_new(&plugin, ESP_GAME_SKYRIMSE, "../../testing-plugins/SkyrimSE/Data/Blank.esm");
  assert(return_code == ESP_OK);

  return_code = esp_plugin_parse(plugin, true);
  assert(return_code == ESP_OK);

  bool is_valid;
  return_code = esp_plugin_is_valid_as_light_master(plugin, &is_valid);
  assert(return_code == ESP_OK);
  assert(is_valid);

  esp_plugin_free(plugin);
}

int main() {
  test_game_id_values();

  test_esp_plugin_new();
  test_esp_plugin_parse();
  test_esp_plugin_filename();
  test_esp_plugin_masters();
  test_esp_plugin_is_master();
  test_esp_plugin_is_light_master();
  test_esp_plugin_is_valid();
  test_esp_plugin_description();
  test_esp_plugin_header_version();
  test_esp_plugin_is_empty();
  test_esp_plugin_count_override_records();
  test_esp_plugin_do_records_overlap();
  test_esp_plugin_is_valid_as_light_master();

  printf("SUCCESS\n");
  return 0;
}
