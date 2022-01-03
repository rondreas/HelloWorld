#include <lx_log.hpp>
#include <lxu_log.hpp>
#include <lxu_command.hpp>

// create a constant string for our "plugin" name
#define SRVNAME_COMMAND	"hello.world"

// create the command,
class CHelloCommand : public CLxCommand
{
  public:
    void execute() LXx_OVERRIDE
    {
      CLxUser_Log log;
      CLxUser_LogService log_service;
      CLxUser_LogEntry entry;

      // Get the master log,
      log_service.GetSubSystem(LXsLOG_LOGSYS, log);

      // Compose and add the entry to log
      log_service.NewEntry(LXe_INFO, "Hello, World!\n", entry);
      log.AddEntry(entry);
    }
};

static CLxMeta_Command<CHelloCommand> cmd_meta(SRVNAME_COMMAND);

static class CRoot : public CLxMetaRoot
{
  bool pre_init() LXx_OVERRIDE
  {
    cmd_meta.set_type_UI();
    add(&cmd_meta);
    return false;
  }
} root_meta;
