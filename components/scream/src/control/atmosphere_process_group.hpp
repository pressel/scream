#ifndef SCREAM_ATMOSPHERE_PROCESS_GROUP_HPP
#define SCREAM_ATMOSPHERE_PROCESS_GROUP_HPP

#include <string>

#include "share/atmosphere_process.hpp"
#include "share/parameter_list.hpp"

namespace scream
{

/*
 *  A class representing a group of atmosphere processes as a single process.
 *
 *  This class allows to create nested lists of processes, by representing a group
 *  of processes as a single atmosphere process.
 *  All the calls to setup/run methods are simply forwarded to the stored list of
 *  atm processes, and the stored list of required/computed fields is simply a
 *  concatenation of the correspong lists in the underlying atm processes.
 */

class AtmosphereProcessGroup : public AtmosphereProcess
{
public:
  using atm_proc_ptr_type = std::shared_ptr<AtmosphereProcess>;

  // Enum to specify whether processes in the group have to be run sequentially or in parallel.
  enum class GroupScheduleType {
    Sequential,
    Parallel
  };

  // Constructor(s)
  explicit AtmosphereProcessGroup (const ParameterList& params);

  virtual ~AtmosphereProcessGroup () = default;

  // The type of the block (e.g., dynamics or physics)
  AtmosphereProcessType type () const { return AtmosphereProcessType::Group; }

  // The name of the block 
  std::string name () const { return m_group_name; }

  // The communicator associated with this atm process
  const Comm& get_comm () const { return m_comm; }

  // The initialization, run, and finalization methods
  void initialize (const Comm& comm);
  void run        (/* what inputs? */);
  void finalize   (/* what inputs? */);

  // Register all fields in the given repo
  void register_fields (FieldRepository<Real, ExecMemSpace>& field_repo) const;

  // The methods used to query the process for its inputs/outputs
  const std::set<FieldIdentifier>&  get_required_fields () const { return m_required_fields; }
  const std::set<FieldIdentifier>&  get_computed_fields () const { return m_computed_fields; }

protected:

  // The methods to set the fields in the process
  void set_required_field_impl (const Field<const Real, ExecMemSpace, MemoryManaged>& f);
  void set_computed_field_impl (const Field<      Real, ExecMemSpace, MemoryManaged>& f);


  // The communicator that each process in this group uses
  Comm              m_comm;

  // The name of the group. This is usually a concatenation of the names of the individual processes
  std::string       m_group_name;
  int               m_group_size;

  // The list of atm processes in this group
  std::vector<atm_proc_ptr_type>  m_atm_processes;

  // The schedule type: Parallel vs Sequential
  GroupScheduleType   m_group_schedule_type;

  // The cumulative list of required/computed fields of the atm processes in the group
  std::set<FieldIdentifier>      m_required_fields;
  std::set<FieldIdentifier>      m_computed_fields;
};

} // namespace scream

#endif // SCREAM_ATMOSPHERE_PROCESS_GROUP_HPP
