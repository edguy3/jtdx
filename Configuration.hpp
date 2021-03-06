// last time modified by Igor UA3DJY on 20200207

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <QObject>
#include <QFont>

#include "Radio.hpp"
#include "AudioDevice.hpp"
#include "Transceiver.hpp"

#include "pimpl_h.hpp"

class QSettings;
class QWidget;
class QAudioDeviceInfo;
class QString;
class QDir;
class Bands;
class FrequencyList;
class StationList;
class QStringListModel;
class QHostAddress;

//
// Class Configuration
//
//  Encapsulates the control, access  and, persistence of user defined
//  settings for the wsjtx GUI.  Setting values are accessed through a
//  QDialog window containing concept orientated tab windows.
//
// Responsibilities
//
//  Provides management of  the CAT and PTT  rig interfaces, providing
//  control access  via a minimal generic  set of Qt slots  and status
//  updates via Qt signals.  Internally  the rig control capability is
//  farmed out  to a  separate thread  since many  of the  rig control
//  functions are blocking.
//
//  All user  settings required by  the wsjtx GUI are  exposed through
//  query methods.  Settings only become  visible once they  have been
//  accepted by the user which is  done by clicking the "OK" button on
//  the settings dialog.
//
//  The QSettings instance  passed to the constructor is  used to read
//  and write user settings.
//
//  Pointers to three QAbstractItemModel  objects are provided to give
//  access to amateur band  information, user working frequencies and,
//  user operating  band information.  These porovide  consistent data
//  models that can  be used in GUI lists or  tables or simply queried
//  for user defined bands, default operating frequencies and, station
//  descriptions.
//
class Configuration final
  : public QObject
{
  Q_OBJECT;
  Q_ENUMS (DataMode Type2MsgGen);

public:
  using MODE = Transceiver::MODE;
  using TransceiverState = Transceiver::TransceiverState;
  using Frequency = Radio::Frequency;
  using port_type = quint16;

  enum DataMode {data_mode_none, data_mode_USB, data_mode_data};
  enum Type2MsgGen {type_2_msg_1_full, type_2_msg_3_full, type_2_msg_5_only};

  explicit Configuration (QSettings * settings, QWidget * parent = nullptr);
  ~Configuration ();

  int exec ();
  bool is_active () const;

  QDir temp_dir () const;
  QDir doc_dir () const;
  QDir data_dir () const;

  QAudioDeviceInfo const& audio_input_device () const;
  AudioDevice::Channel audio_input_channel () const;
  QAudioDeviceInfo const& audio_output_device () const;
  AudioDevice::Channel audio_output_channel () const;

  // These query methods should be used after a call to exec() to
  // determine if either the audio input or audio output stream
  // parameters have changed. The respective streams should be
  // re-opened if they return true.
  bool restart_audio_input () const;
  bool restart_audio_output () const;

  QString my_callsign () const;
  QString my_grid () const;
  QString timeFrom () const;
  QString content () const;
  QString countries () const;
  QString callsigns () const;
  QFont decoded_text_font () const;
  qint32 id_interval () const;
  qint32 ntrials() const;
  qint32 ntrials10() const;
  qint32 ntrialsrxf10() const;
  qint32 npreampass() const;
  qint32 aggressive() const;
  qint32 harmonicsdepth() const;
  qint32 nsingdecatt() const;
  qint32 ntopfreq65() const;
  qint32 nAnswerCQCounter() const;
  qint32 nAnswerInCallCounter() const;
  qint32 nSentRReportCounter() const;
  qint32 nSentRR7373Counter() const;
  double txDelay() const;
  bool fmaskact() const;
  bool answerCQCount() const;
  bool answerInCallCount() const;
  bool sentRReportCount() const;
  bool sentRR7373Count() const;
  bool strictdirCQ() const;
  bool halttxreplyother() const;
  bool hidefree() const;
  bool hide2ndHash() const;
  bool showcq() const;
  bool showcqrrr73() const;
  bool showcq73() const;
  bool enableContent() const;
  bool enableCountryFilter() const;
  bool enableCallsignFilter() const;
  bool do_snr() const;
  bool do_pwr() const;
  bool id_after_73 () const;
  bool tx_QSY_allowed () const;
  bool spot_to_psk_reporter () const;
  bool spot_to_dxsummit () const;
  bool prevent_spotting_false () const;
  bool filterUDP () const;
  bool send_to_eqsl () const;
  QString eqsl_username () const;
  QString eqsl_passwd () const;
  QString eqsl_nickname () const;
  bool usesched() const;
  QString sched_hh_1 () const;
  QString sched_mm_1 () const;
  QString sched_band_1 () const;
  bool sched_mix_1 () const;
  QString sched_hh_2 () const;
  QString sched_mm_2 () const;
  QString sched_band_2 () const;
  bool sched_mix_2 () const;
  QString sched_hh_3 () const;
  QString sched_mm_3 () const;
  QString sched_band_3 () const;
  bool sched_mix_3 () const;
  QString sched_hh_4 () const;
  QString sched_mm_4 () const;
  QString sched_band_4 () const;
  bool sched_mix_4 () const;
  QString sched_hh_5 () const;
  QString sched_mm_5 () const;
  QString sched_band_5 () const;
  bool sched_mix_5 () const;
  bool monitor_off_at_startup () const;
  bool monitor_last_used () const;
  bool log_as_RTTY () const;
  bool report_in_comments () const;
  bool prompt_to_log () const;
  bool autolog () const;
  bool insert_blank () const;
  bool countryName () const;
  bool countryPrefix () const;
  bool callNotif () const;
  bool gridNotif () const;
  bool otherMessagesMarker () const;
  bool RR73Marker () const;
  bool redMarker () const;
  bool blueMarker () const;
  bool txtColor () const;
  bool workedStriked () const;
  bool workedUnderlined () const;
  bool workedColor () const;
  bool workedDontShow () const;
  bool newDXCC () const;
  bool newDXCCBand () const;
  bool newDXCCBandMode () const;
  bool newPx () const;
  bool newPxBand () const;
  bool newPxBandMode () const;
  bool newCall () const;
  bool newCallBand () const;
  bool newCallBandMode () const;
  bool newGrid () const;
  bool newGridBand () const;
  bool newGridBandMode () const;
  bool newPotential() const;
  QString hideContinents() const;
  bool clear_DX () const;
  bool clear_DX_exit () const;
  bool miles () const;
  int watchdog () const;
  int tunetimer () const;
  bool TX_messages () const;
  bool hide_TX_messages () const;
  bool split_mode () const;
  bool decode_at_52s () const;
  bool beepOnMyCall () const;
  bool beepOnNewDXCC () const;
  bool beepOnNewGrid () const;
  bool beepOnNewPx () const;
  bool beepOnNewCall () const;
  bool beepOnFirstMsg () const;
  bool post_decodes () const;
  QString udp_server_name () const;
  port_type udp_server_port () const;
  QString udp2_server_name () const;
  port_type udp2_server_port () const;
  QString tcp_server_name () const;
  port_type tcp_server_port () const;
  bool valid_udp2 () const;
  bool accept_udp_requests () const;
  bool enable_udp1_adif_sending () const;
  bool enable_udp2_broadcast () const;
  bool enable_tcp_connection () const;
  bool write_decoded () const;
  bool write_decoded_debug () const;
  bool udpWindowToFront () const;
  bool udpWindowRestore () const;
  Bands * bands ();
  Bands const * bands () const;
  FrequencyList * frequencies ();
  FrequencyList const * frequencies () const;
  StationList * stations ();
  StationList const * stations () const;
  QStringListModel * macros ();
  QStringListModel const * macros () const;
  QDir save_directory () const;
  QString rig_name () const;
  Type2MsgGen type_2_msg_gen () const;
  QColor color_CQ () const;
  QColor color_MyCall () const;
  QColor color_TxMsg () const;
  QColor color_NewDXCC () const;
  QColor color_NewDXCCBand () const;
  QColor color_NewCall () const;
  QColor color_NewCallBand () const;
  QColor color_NewPx () const;
  QColor color_NewPxBand () const;
  QColor color_NewGrid () const;
  QColor color_NewGridBand () const;
  QColor color_StandardCall () const;
  QColor color_WorkedCall () const;
  bool pwrBandTxMemory () const;
  bool pwrBandTuneMemory () const;

  // This method queries if a CAT and PTT connection is operational.
  bool is_transceiver_online () const;

  // Start the rig connection, safe and normal to call when rig is
  // already open.
  bool transceiver_online ();

  // check if a real rig is configured
  bool is_dummy_rig () const;

  // Frequency resolution of the rig
  //
  //  0 - 1Hz
  //  1 - 10Hz rounded
  // -1 - 10Hz truncated
  //  2 - 100Hz rounded
  // -2 - 100Hz truncated
  int transceiver_resolution () const;

  // Close down connection to rig.
  void transceiver_offline ();
  void add_callsign_hideFilter (QString);

  // Set transceiver frequency in Hertz.
  Q_SLOT void transceiver_frequency (Frequency);

  // Setting a non zero TX frequency means split operation
  // rationalise_mode means ensure TX uses same mode as RX.
  Q_SLOT void transceiver_tx_frequency (Frequency = 0u);

  // Set transceiver mode.
  //
  // Rationalise means ensure TX uses same mode as RX.
  Q_SLOT void transceiver_mode (MODE);

  // Set/unset PTT.
  //
  // Note that this must be called even if VOX PTT is selected since
  // the "Emulate Split" mode requires PTT information to coordinate
  // frequency changes.
  Q_SLOT void transceiver_ptt (bool = true);

  // Attempt to (re-)synchronise transceiver state.
  //
  // Force signal guarantees either a transceiver_update or a
  // transceiver_failure signal.
  //
  // The enforce_mode_and_split parameter ensures that future
  // transceiver updates have the correct mode and split setting
  // i.e. the transceiver is ready for use.
  Q_SLOT void sync_transceiver (bool force_signal = false, bool enforce_mode_and_split = false);


  //
  // This signal indicates that a font has been selected and accepted
  // for the decoded text.
  //
  Q_SIGNAL void decoded_text_font_changed (QFont);

  //
  // This signal is emitted when the UDP server changes
  //
  Q_SIGNAL void udp_server_changed (QString const& udp_server);
  Q_SIGNAL void udp_server_port_changed (port_type server_port);
  Q_SIGNAL void tcp_server_changed (QString const& tcp_server);
  Q_SIGNAL void tcp_server_port_changed (port_type server_port);

  //
  // These signals are emitted and reflect transceiver state changes
  //

  // signals a change in one of the TransceiverState members
  Q_SIGNAL void transceiver_update (Transceiver::TransceiverState const&) const;

  // Signals a failure of a control rig CAT or PTT connection.
  //
  // A failed rig CAT or PTT connection is fatal and the underlying
  // connections are closed automatically. The connections can be
  // re-established with a call to transceiver_online(true) assuming
  // the fault condition has been rectified or is transient.
  Q_SIGNAL void transceiver_failure (QString const& reason) const;

private:
  class impl;
  pimpl<impl> m_;
};


Q_DECLARE_METATYPE (Configuration::DataMode);
Q_DECLARE_METATYPE (Configuration::Type2MsgGen);

#if !defined (QT_NO_DEBUG_STREAM)
ENUM_QDEBUG_OPS_DECL (Configuration, DataMode);
ENUM_QDEBUG_OPS_DECL (Configuration, Type2MsgGen);
#endif

ENUM_QDATASTREAM_OPS_DECL (Configuration, DataMode);
ENUM_QDATASTREAM_OPS_DECL (Configuration, Type2MsgGen);

ENUM_CONVERSION_OPS_DECL (Configuration, DataMode);
ENUM_CONVERSION_OPS_DECL (Configuration, Type2MsgGen);

#endif
