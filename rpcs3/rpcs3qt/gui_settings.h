#ifndef GUI_SETTINGS_H
#define GUI_SETTINGS_H

#include "Utilities/Log.h"

#include <QSettings>
#include <QDir>
#include <QVariant>
#include <QSize>

typedef struct GUI_SAVE
{
	QString key;
	QString name;
	QVariant def;

	GUI_SAVE() {
		key = "";
		name = "";
		def = QVariant();
	};
	GUI_SAVE(const QString& k, const QString& n, const QVariant& d) {
		key = k;
		name = n;
		def = d;
	};
};

typedef std::map<const QString, const QSize> icon_size;

namespace GUI
{
	const QString gl_icon_key_small  = "small";
	const QString gl_icon_key_medium = "medium";
	const QString gl_icon_key_large  = "large";

	const icon_size gl_icon_size = {
		{ gl_icon_key_small,  QSize(80, 44) },
		{ gl_icon_key_medium, QSize(160, 88) },
		{ gl_icon_key_large,  QSize(320, 176) }
	};

	const QString main_window = "main_window";
	const QString game_list   = "GameList";
	const QString logger      = "Logger";
	const QString meta        = "Meta";

	const GUI_SAVE ib_pkg_success = GUI_SAVE( main_window, "infoBoxEnabledInstallPKG", true );
	const GUI_SAVE ib_pup_success = GUI_SAVE( main_window, "infoBoxEnabledInstallPUP", true );
	const GUI_SAVE ib_show_welcome = GUI_SAVE(main_window, "infoBoxEnabledWelcome", true);

	const GUI_SAVE fd_install_pkg  = GUI_SAVE( main_window, "lastExplorePathPKG",  "" );
	const GUI_SAVE fd_install_pup  = GUI_SAVE( main_window, "lastExplorePathPUP",  "" );
	const GUI_SAVE fd_boot_elf     = GUI_SAVE( main_window, "lastExplorePathELF",  "" );
	const GUI_SAVE fd_boot_game    = GUI_SAVE( main_window, "lastExplorePathGAME", "" );
	const GUI_SAVE fd_decrypt_sprx = GUI_SAVE( main_window, "lastExplorePathSPRX", "" );

	const GUI_SAVE mw_debugger    = GUI_SAVE( main_window, "debuggerVisible", false );
	const GUI_SAVE mw_logger      = GUI_SAVE( main_window, "loggerVisible",   true );
	const GUI_SAVE mw_gamelist    = GUI_SAVE( main_window, "gamelistVisible", true );
	const GUI_SAVE mw_controls    = GUI_SAVE( main_window, "controlsVisible", true );
	const GUI_SAVE mw_geometry    = GUI_SAVE( main_window, "geometry",        QByteArray() );
	const GUI_SAVE mw_windowState = GUI_SAVE( main_window, "windowState",     QByteArray() );

	const GUI_SAVE cat_hdd_game    = GUI_SAVE( game_list, "categoryVisibleHDDGame",    true );
	const GUI_SAVE cat_disc_game   = GUI_SAVE( game_list, "categoryVisibleDiscGame",   true );
	const GUI_SAVE cat_home        = GUI_SAVE( game_list, "categoryVisibleHome",       true );
	const GUI_SAVE cat_audio_video = GUI_SAVE( game_list, "categoryVisibleAudioVideo", true );
	const GUI_SAVE cat_game_data   = GUI_SAVE( game_list, "categoryVisibleGameData",   true );
	const GUI_SAVE cat_unknown     = GUI_SAVE( game_list, "categoryVisibleUnknown",    true );
	const GUI_SAVE cat_other       = GUI_SAVE( game_list, "categoryVisibleOther",      true );

	const GUI_SAVE gl_sortAsc  = GUI_SAVE( game_list, "sortAsc",  true );
	const GUI_SAVE gl_sortCol  = GUI_SAVE( game_list, "sortCol",  1 );
	const GUI_SAVE gl_state    = GUI_SAVE( game_list, "state",    QByteArray() );
	const GUI_SAVE gl_iconSize = GUI_SAVE( game_list, "iconSize", gl_icon_key_small);

	const GUI_SAVE l_tty   = GUI_SAVE( logger, "TTY",   true );
	const GUI_SAVE l_level = GUI_SAVE( logger, "level", (uint)(logs::level::success) );

	const GUI_SAVE m_currentConfig     = GUI_SAVE(meta, "currentConfig",     QObject::tr("CurrentSettings"));
	const GUI_SAVE m_currentStylesheet = GUI_SAVE(meta, "currentStylesheet", QObject::tr("default"));
}

/** Class for GUI settings..
*/
class gui_settings : public QObject
{
	Q_OBJECT

public:
	explicit gui_settings(QObject* parent = nullptr);
	~gui_settings();

	QString GetSettingsDir() {
		return settingsDir.absolutePath();
	}

	/** Changes the settings file to the destination preset*/
	void ChangeToConfig(const QString& destination);

	bool GetCategoryVisibility(QString cat);
	QVariant GetValue(const GUI_SAVE& entry);

	void ShowInfoBox(const GUI_SAVE& entry, const QString& title, const QString& text, QWidget* parent = 0);

	logs::level GetLogLevel();
	bool GetGamelistColVisibility(int col);
	QStringList GetConfigEntries();
	QString GetCurrentStylesheetPath();
	QStringList GetStylesheetEntries();
	QStringList GetGameListCategoryFilters();

public slots:
	void Reset(bool removeMeta = false);

	/** Write value to entry */
	void SetValue(const GUI_SAVE& entry, const QVariant& value);

	/** Sets the visibility of the chosen category. */
	void SetCategoryVisibility(const QString& cat, const bool& val);

	void SetGamelistColVisibility(int col, bool val);

	void SaveCurrentConfig(const QString& friendlyName);

private:
	QString ComputeSettingsDir();
	void BackupSettingsToTarget(const QString& destination);

	QSettings settings;
	QDir settingsDir;
};

#endif
