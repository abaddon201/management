
///@fixme(abby) just for test
#include "internal/factory.h"
#include "internal/market.h"
#include "internal/player.h"
#include "internal/ruleset.h"
#include "internal/session.h"
#include "internal/storage.h"
#include "internal/server.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
///

int main() {
  Server serv(8989);
  int res = serv.start();
  printf("habahaba\n");
  printf("%d\n", res);
  return 0;
}
