#pragma once

#include "Scene.h"
#include "GLRenderer.h"
#include "GLUtils.h"
#include "TransformTool.h"
#include <QOpenGLWidget>
#include <QString>

/// @class GLViewport
/// @brief our main gl window widget - viewport drawing happens here
class GLViewport : public QOpenGLWidget
{
// must include this if we want to use Qt signals/slots
Q_OBJECT

public :
	explicit GLViewport( QWidget* parent = nullptr,
	                     Qt::WindowFlags format = Qt::WindowFlags() );
	~GLViewport();

/// @brief set the scene to render
	inline void setScene( Scene* scene )
	{
		m_scene = scene;
	}

	inline void setSelection( bool selection )
	{
		m_selection = selection;
//		m_selectionTransform.reset();
	}

	inline bool getSelection() const
	{
		return m_selection;
	}

	inline void setSelectionTransform( const mg::Matrix4D& transform )
	{
		UNUSED_VALUE( transform );
//		m_selectionTransform.reset();
//		m_selectionTransform.setTransform(transform);
//		updateGL();
	}

	inline mg::Matrix4D getSelectionTransform()
	{
		return mg::Matrix4D();
//		return m_selectionTransform.getTransform();
	}

protected:
//  following methods must be implimented in the sub class
/// @brief called when the window is created
	void initializeGL() override;

/// @brief called whenever the window is re-sized
/// @param[in] w the width of the resized window
/// @param[in] h the height of the resized window
	void resizeGL( int w, int h ) override;

/// @brief main gl drawing routine which is called whenever the window needs to be re-drawn
	void paintGL() override;

	void mousePressEvent( QMouseEvent* event ) override;
	void mouseMoveEvent( QMouseEvent* event ) override;
	void mouseReleaseEvent( QMouseEvent* event ) override;

private:
	const Scene* m_scene = nullptr; ///< scene to render

	GLRenderer m_renderer;
	Camera m_cam; ///< viewport camera
	GLDrawable m_refGrid; ///< reference grid
	GLDrawable m_hair; ///< hair
	DrawList m_drawList; ///< list of drawable objects created for each mesh in scene

//	TODO fix: ngl::Text* m_text; ///< debug info overlay

// mouse controls
/// @brief flag that marks that transformations calculated on mouse movement
/// apply to an object and not the camera
	bool m_selection = false;
/// @brief transform handle
	TransformHandle m_transformHdl;
/// @brief the previous x mouse value
	int m_mouseX = 0;
/// @brief the previous y mouse value
	int m_mouseY = 0;
};
